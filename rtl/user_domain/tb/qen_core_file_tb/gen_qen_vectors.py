#!/usr/bin/env python3

from dataclasses import dataclass
import random
from pathlib import Path


POS_WIDTH = 32
SAMPLE_WIDTH = 32


def signed_wrap(value: int, width: int = 32) -> int:
    mask = (1 << width) - 1
    value &= mask
    if value & (1 << (width - 1)):
        value -= (1 << width)
    return value


def transition_step(prev_ab: int, curr_ab: int):
    transition = ((prev_ab & 0x3) << 2) | (curr_ab & 0x3)

    forward = {
        0b0001,  # 00 -> 01
        0b0111,  # 01 -> 11
        0b1110,  # 11 -> 10
        0b1000,  # 10 -> 00
    }

    reverse = {
        0b0010,  # 00 -> 10
        0b1011,  # 10 -> 11
        0b1101,  # 11 -> 01
        0b0100,  # 01 -> 00
    }

    same = {
        0b0000,
        0b0101,
        0b1010,
        0b1111,
    }

    if transition in forward:
        return +1, False
    if transition in reverse:
        return -1, False
    if transition in same:
        return 0, False

    return 0, True


@dataclass
class QenModel:
    enabled: int = 0
    prev_ab: int = 0
    z_q: int = 0

    position: int = 0
    velocity: int = 0
    delta: int = 0
    sample_position: int = 0
    index_position: int = 0

    direction: int = 1
    index_seen: int = 0
    error_count: int = 0

    invalid_transition: int = 0
    velocity_valid: int = 0
    sample_counter: int = 0

    def step(
        self,
        enable: int,
        clear_position: int,
        clear_error: int,
        index_reset_enable: int,
        sample_period: int,
        a: int,
        b: int,
        z: int,
    ):
        curr_ab = ((b & 1) << 1) | (a & 1)

        step, invalid = transition_step(self.prev_ab, curr_ab)
        position_after_step = signed_wrap(self.position + step) if step != 0 else self.position

        sample_period_eff = sample_period if sample_period != 0 else 1
        sample_now = self.sample_counter >= (sample_period_eff - 1)
        sample_delta = signed_wrap(position_after_step - self.sample_position)

        z_rise = (z == 1) and (self.z_q == 0)

        # Default pulse outputs clear every cycle.
        self.invalid_transition = 0
        self.velocity_valid = 0

        # RTL updates z_q every non-reset clock.
        self.z_q = z & 1

        # clear_error is independent, but invalid transition does not increment
        # in the same cycle when clear_error is asserted.
        if clear_error:
            self.error_count = 0

        if clear_position:
            self.enabled = 1 if enable else 0
            self.prev_ab = curr_ab

            self.position = 0
            self.velocity = 0
            self.delta = 0
            self.sample_position = 0
            self.index_position = 0

            self.index_seen = 0
            self.sample_counter = 0

        elif not enable:
            self.enabled = 0
            self.prev_ab = curr_ab
            self.sample_counter = 0

        else:
            if not self.enabled:
                # First enabled cycle initializes previous AB state only.
                self.enabled = 1
                self.prev_ab = curr_ab
                self.sample_position = self.position
                self.sample_counter = 0

            else:
                self.prev_ab = curr_ab

                if step != 0:
                    self.position = position_after_step
                    self.direction = 1 if step == 1 else 0

                if invalid:
                    self.invalid_transition = 1
                    if not clear_error:
                        self.error_count = (self.error_count + 1) & 0xFFFFFFFF

                if z_rise:
                    self.index_seen = 1
                    self.index_position = position_after_step

                    if index_reset_enable:
                        self.position = 0
                        self.velocity = 0
                        self.delta = 0
                        self.sample_position = 0
                        self.sample_counter = 0

                elif sample_now:
                    self.delta = sample_delta
                    self.velocity = sample_delta
                    self.sample_position = position_after_step
                    self.sample_counter = 0
                    self.velocity_valid = 1

                else:
                    self.sample_counter = (self.sample_counter + 1) & ((1 << SAMPLE_WIDTH) - 1)

        return {
            "position": self.position,
            "velocity": self.velocity,
            "delta": self.delta,
            "direction": self.direction,
            "index_seen": self.index_seen,
            "index_position": self.index_position,
            "error_count": self.error_count,
            "invalid_transition": self.invalid_transition,
            "velocity_valid": self.velocity_valid,
            "ab_state": curr_ab,
        }


def ab_to_a_b(ab: int):
    return ab & 1, (ab >> 1) & 1


def main():
    here = Path(__file__).resolve().parent
    stim_dir = here / "stimuli"
    stim_dir.mkdir(parents=True, exist_ok=True)

    stim_path = stim_dir / "stimuli.txt"
    exp_path = stim_dir / "expected_response.txt"

    model = QenModel()
    rows = []
    expected = []

    cycle = 0

    def add(
        ab: int,
        *,
        enable: int = 1,
        clear_position: int = 0,
        clear_error: int = 0,
        index_reset_enable: int = 0,
        sample_period: int = 4,
        z: int = 0,
        repeat: int = 1,
    ):
        nonlocal cycle

        a, b = ab_to_a_b(ab)

        for _ in range(repeat):
            out = model.step(
                enable=enable,
                clear_position=clear_position,
                clear_error=clear_error,
                index_reset_enable=index_reset_enable,
                sample_period=sample_period,
                a=a,
                b=b,
                z=z,
            )

            rows.append(
                (
                    cycle,
                    enable,
                    clear_position,
                    clear_error,
                    index_reset_enable,
                    sample_period,
                    a,
                    b,
                    z,
                )
            )

            expected.append(
                (
                    cycle,
                    out["position"],
                    out["velocity"],
                    out["delta"],
                    out["direction"],
                    out["index_seen"],
                    out["index_position"],
                    out["error_count"],
                    out["invalid_transition"],
                    out["velocity_valid"],
                    out["ab_state"],
                )
            )

            cycle += 1

    # Disabled settling. No movement should be counted.
    add(0b00, enable=0, repeat=2)

    # Clear and enable at AB=00. This initializes the decoder.
    add(0b00, enable=1, clear_position=1, clear_error=1)

    # Forward: 00 -> 01 -> 11 -> 10 -> 00, repeated twice.
    for ab in [0b01, 0b11, 0b10, 0b00] * 2:
        add(ab)

    # Reverse: 00 -> 10 -> 11 -> 01 -> 00.
    for ab in [0b10, 0b11, 0b01, 0b00]:
        add(ab)

    # Invalid jump: 00 -> 11. Position should not change, error_count increments.
    add(0b11)

    # Recover with valid forward transitions 11 -> 10 -> 00.
    for ab in [0b10, 0b00]:
        add(ab)

    # Clear only the error counter.
    add(0b00, clear_error=1)

    # Index pulse without position reset. On 00 -> 01 with Z high,
    # index_position should capture the post-step position.
    add(0b01, z=1)
    add(0b11, z=0)
    add(0b10)
    add(0b00)

    # Clear position and test index reset mode.
    add(0b00, clear_position=1, clear_error=1, index_reset_enable=1)

    # Move forward to +4; pulse Z on the last transition. The index position
    # captures +4, then position resets to 0.
    for ab in [0b01, 0b11, 0b10]:
        add(ab, index_reset_enable=1)
    add(0b00, z=1, index_reset_enable=1)
    add(0b00, z=0, index_reset_enable=1)

    # Clear again and move reverse twice around the quadrature cycle.
    add(0b00, clear_position=1, clear_error=1)

    for ab in [0b10, 0b11, 0b01, 0b00] * 2:
        add(ab)

    # Disable behavior: changes while disabled should not count and should not error.
    add(0b00, enable=0)
    add(0b11, enable=0)

    # Re-enable at 11. First enabled cycle only initializes previous state.
    add(0b11, enable=1)

    # Valid forward from 11 -> 10.
    add(0b10, enable=1)

    # Random stress test.
    # Fixed seed makes failures reproducible.
    rng = random.Random(0x51454E)  # "QEN"

    for _ in range(10000):
        add(
            ab=rng.randint(0, 3),
            enable=rng.choices([0, 1], weights=[5, 95])[0],
            clear_position=rng.choices([0, 1], weights=[99, 1])[0],
            clear_error=rng.choices([0, 1], weights=[95, 5])[0],
            index_reset_enable=rng.choice([0, 1]),
            sample_period=rng.randint(2, 10),
            z=rng.choices([0, 1], weights=[90, 10])[0],
        )

    with stim_path.open("w", encoding="utf-8") as f:
        for row in rows:
            f.write("%d %d %d %d %d %d %d %d %d\n" % row)

    with exp_path.open("w", encoding="utf-8") as f:
        for row in expected:
            f.write("%d %d %d %d %d %d %d %d %d %d %d\n" % row)

    print(f"Wrote {stim_path}")
    print(f"Wrote {exp_path}")
    print(f"Generated {len(rows)} QEN vectors")


if __name__ == "__main__":
    main()
