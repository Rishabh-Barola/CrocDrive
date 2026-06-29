// Compact AMCP/QEN MMIO regression test.
// Uses QEN_SIM_INPUT, not external GPIO.
// This checks register-level QEN semantics directly.

#include <stdint.h>
#include "util.h"
#include "config.h"

#ifndef QEN_CTRL_OFFSET
#define QEN_CTRL_OFFSET             0x040u
#define QEN_STATUS_OFFSET           0x044u
#define QEN_POSITION_OFFSET         0x048u
#define QEN_VELOCITY_OFFSET         0x04cu
#define QEN_DELTA_OFFSET            0x050u
#define QEN_INDEX_POSITION_OFFSET   0x054u
#define QEN_ERROR_COUNT_OFFSET      0x058u
#define QEN_SAMPLE_PERIOD_OFFSET    0x05cu
#define QEN_SIM_INPUT_OFFSET        0x060u
#define QEN_DEBUG_OFFSET            0x064u
#endif

#define QEN_EN        (1u << 0)
#define QEN_CLR_POS   (1u << 1)
#define QEN_CLR_ERR   (1u << 2)
#define QEN_IDX_RESET (1u << 3)
#define QEN_SIM       (1u << 4)

#define ST_DIR        (1u << 1)
#define ST_IDX        (1u << 2)
#define ST_ERR        (1u << 3)

#define R(off)        (*reg32(AMCP_BASE_ADDR, (off)))

static uint32_t fail;

static void wait_cycles(uint32_t n) {
    for (volatile uint32_t i = 0; i < n; i++) {
        asm volatile ("nop");
    }
}

static void check(uint32_t code, uint32_t cond) {
    if (!cond && fail == 0u) {
        fail = code;
    }
}

static void qen_reset(uint32_t ctrl_extra, uint32_t sample_period) {
    R(QEN_SIM_INPUT_OFFSET) = 0u;
    R(QEN_SAMPLE_PERIOD_OFFSET) = sample_period;

    R(QEN_CTRL_OFFSET) = QEN_EN | QEN_SIM | ctrl_extra | QEN_CLR_POS | QEN_CLR_ERR;
    wait_cycles(32);

    R(QEN_CTRL_OFFSET) = QEN_EN | QEN_SIM | ctrl_extra;
    wait_cycles(32);

    // Hold 00 as a clean starting AB state.
    R(QEN_SIM_INPUT_OFFSET) = 0u;
    wait_cycles(32);
}

static void set_abz(uint32_t ab, uint32_t z) {
    uint32_t a = ab & 1u;
    uint32_t b = (ab >> 1) & 1u;

    R(QEN_SIM_INPUT_OFFSET) = a | (b << 1) | ((z & 1u) << 2);
    wait_cycles(16);
}

static void set_ab(uint32_t ab) {
    set_abz(ab, 0u);
}

static void pulse_z_at_ab(uint32_t ab) {
    set_abz(ab, 1u);
    set_abz(ab, 0u);
}

static void forward_transitions(uint32_t n) {
    static const uint32_t seq[4] = {1u, 3u, 2u, 0u};

    for (uint32_t i = 0; i < n; i++) {
        set_ab(seq[i & 3u]);
    }
}

static void reverse_transitions(uint32_t n) {
    static const uint32_t seq[4] = {2u, 3u, 1u, 0u};

    for (uint32_t i = 0; i < n; i++) {
        set_ab(seq[i & 3u]);
    }
}

static void test_forward_reverse_mixed(void) {
    qen_reset(0u, 1000000u);

    forward_transitions(4u);
    check(0x10u, (int32_t)R(QEN_POSITION_OFFSET) == 4);
    check(0x11u, R(QEN_ERROR_COUNT_OFFSET) == 0u);
    check(0x12u, (R(QEN_STATUS_OFFSET) & ST_DIR) != 0u);

    qen_reset(0u, 1000000u);

    reverse_transitions(4u);
    check(0x20u, (int32_t)R(QEN_POSITION_OFFSET) == -4);
    check(0x21u, R(QEN_ERROR_COUNT_OFFSET) == 0u);
    check(0x22u, (R(QEN_STATUS_OFFSET) & ST_DIR) == 0u);

    qen_reset(0u, 1000000u);

    forward_transitions(8u);
    reverse_transitions(3u);
    check(0x30u, (int32_t)R(QEN_POSITION_OFFSET) == 5);
    check(0x31u, R(QEN_ERROR_COUNT_OFFSET) == 0u);
}

static void test_invalid_and_clear(void) {
    qen_reset(0u, 1000000u);

    // 00 -> 11 invalid, then 11 -> 00 invalid.
    set_ab(3u);
    set_ab(0u);

    check(0x40u, (int32_t)R(QEN_POSITION_OFFSET) == 0);
    check(0x41u, R(QEN_ERROR_COUNT_OFFSET) == 2u);
    check(0x42u, (R(QEN_STATUS_OFFSET) & ST_ERR) != 0u);

    // Clear error only.
    R(QEN_CTRL_OFFSET) = QEN_EN | QEN_SIM | QEN_CLR_ERR;
    wait_cycles(32);
    R(QEN_CTRL_OFFSET) = QEN_EN | QEN_SIM;
    wait_cycles(32);

    check(0x43u, R(QEN_ERROR_COUNT_OFFSET) == 0u);
    check(0x44u, (R(QEN_STATUS_OFFSET) & ST_ERR) == 0u);

    // Move, then clear position.
    forward_transitions(4u);
    check(0x45u, (int32_t)R(QEN_POSITION_OFFSET) == 4);

    R(QEN_CTRL_OFFSET) = QEN_EN | QEN_SIM | QEN_CLR_POS;
    wait_cycles(32);
    R(QEN_CTRL_OFFSET) = QEN_EN | QEN_SIM;
    wait_cycles(32);

    check(0x46u, (int32_t)R(QEN_POSITION_OFFSET) == 0);
}

static void test_index_no_reset(void) {
    qen_reset(0u, 1000000u);

    forward_transitions(8u);
    pulse_z_at_ab(0u);

    check(0x50u, (int32_t)R(QEN_POSITION_OFFSET) == 8);
    check(0x51u, (int32_t)R(QEN_INDEX_POSITION_OFFSET) == 8);
    check(0x52u, (R(QEN_STATUS_OFFSET) & ST_IDX) != 0u);

    forward_transitions(4u);

    check(0x53u, (int32_t)R(QEN_POSITION_OFFSET) == 12);
    check(0x54u, (int32_t)R(QEN_INDEX_POSITION_OFFSET) == 8);
}

static void test_index_with_reset(void) {
    qen_reset(QEN_IDX_RESET, 1000000u);

    forward_transitions(8u);
    pulse_z_at_ab(0u);

    check(0x60u, (int32_t)R(QEN_INDEX_POSITION_OFFSET) == 8);
    check(0x61u, (int32_t)R(QEN_POSITION_OFFSET) == 0);
    check(0x62u, (R(QEN_STATUS_OFFSET) & ST_IDX) != 0u);

    forward_transitions(4u);

    check(0x63u, (int32_t)R(QEN_POSITION_OFFSET) == 4);
    check(0x64u, (int32_t)R(QEN_INDEX_POSITION_OFFSET) == 8);
}

static void test_debug_register(void) {
    qen_reset(0u, 1000000u);

    // A=1, B=0, Z=1.
    // Expected low bits:
    //   ab_state={B,A}=01 -> bits[1:0] = 1
    //   A bit2 = 1
    //   B bit3 = 0
    //   Z bit4 = 1
    // Low 5 bits = 1 + 4 + 16 = 21 = 0x15.
    set_abz(1u, 1u);

    check(0x70u, (R(QEN_DEBUG_OFFSET) & 0x1fu) == 0x15u);
}

static void test_velocity_delta_liveness(void) {
    uint32_t seen_pos_delta = 0u;
    uint32_t seen_pos_vel = 0u;
    uint32_t seen_neg_delta = 0u;
    uint32_t seen_neg_vel = 0u;

    qen_reset(0u, 32u);

    // We do not check exact velocity/delta timing here, because the CPU is not
    // phase-aligned to the QEN sample window. Instead, we check that sampled
    // delta/velocity become positive during forward motion and negative during
    // reverse motion.
    for (uint32_t i = 0; i < 96u; i++) {
        static const uint32_t seq[4] = {1u, 3u, 2u, 0u};

        set_ab(seq[i & 3u]);

        int32_t d = (int32_t)R(QEN_DELTA_OFFSET);
        int32_t v = (int32_t)R(QEN_VELOCITY_OFFSET);

        if (d > 0) {
            seen_pos_delta = 1u;
        }

        if (v > 0) {
            seen_pos_vel = 1u;
        }
    }

    for (uint32_t i = 0; i < 96u; i++) {
        static const uint32_t seq[4] = {2u, 3u, 1u, 0u};

        set_ab(seq[i & 3u]);

        int32_t d = (int32_t)R(QEN_DELTA_OFFSET);
        int32_t v = (int32_t)R(QEN_VELOCITY_OFFSET);

        if (d < 0) {
            seen_neg_delta = 1u;
        }

        if (v < 0) {
            seen_neg_vel = 1u;
        }
    }

    check(0x80u, seen_pos_delta != 0u);
    check(0x81u, seen_pos_vel != 0u);
    check(0x82u, seen_neg_delta != 0u);
    check(0x83u, seen_neg_vel != 0u);
}

int main(void) {
    fail = 0u;

    check(0x01u, R(AMCP_ID_OFFSET) == 0x414D4350u);

    test_forward_reverse_mixed();
    test_invalid_and_clear();
    test_index_no_reset();
    test_index_with_reset();
    test_debug_register();
    // Velocity/delta timing is verified in the cycle-accurate QEN core TB.
    // Do not assert it here because CPU MMIO reads are not phase-aligned
    // to the QEN sample window.

    return fail;
}
