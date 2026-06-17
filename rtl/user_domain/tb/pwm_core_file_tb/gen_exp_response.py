def parse_stimulus(line):
    line = line.strip()
    polarity = int(line[0], 2)
    period = int(line[1:17], 2)
    duty = int(line[17:33], 2)
    samples = int(line[33:49], 2)
    return polarity, period, duty, samples

def clamp_duty(period, duty):
    if period == 0:
        return 0
    return min(duty, period)

def pwm_model(polarity, period, duty, samples):
    """
    Golden model matched to pwm_core.sv.

    Sampling convention:
    sample 0 is taken after enable has been asserted and the active
    period/duty registers have loaded. Therefore counter starts at 0.
    """
    counter = 0
    period_active = period
    duty_active = clamp_duty(period, duty)

    for _ in range(samples):
        if period_active == 0:
            pwm = 0
            period_done = 0
            period_zero = 1
            counter = 0
        else:
            raw = 1 if counter < duty_active else 0
            pwm = (1 - raw) if polarity else raw
            period_done = 1 if counter == period_active - 1 else 0
            period_zero = 0

        yield {
            "pwm": pwm,
            "period_done": period_done,
            "period_zero": period_zero,
            "counter": counter,
            "period_active": period_active,
            "duty_active": duty_active,
        }

        if period_active == 0:
            counter = 0
        elif counter == period_active - 1:
            counter = 0
        else:
            counter += 1

def write_expected(input_filename, output_filename):
    with open(input_filename, "r") as infile, open(output_filename, "w") as outfile:
        for line in infile:
            if not line.strip():
                continue

            polarity, period, duty, samples = parse_stimulus(line)

            for rsp in pwm_model(polarity, period, duty, samples):
                # Format:
                # pwm[0] period_done[0] period_zero[0]
                # counter[15:0] period_active[15:0] duty_active[15:0]
                out = (
                    f"{rsp['pwm']:01b}"
                    f"{rsp['period_done']:01b}"
                    f"{rsp['period_zero']:01b}"
                    f"{rsp['counter']:016b}"
                    f"{rsp['period_active']:016b}"
                    f"{rsp['duty_active']:016b}"
                )
                outfile.write(out + "\n")

if __name__ == "__main__":
    write_expected("stimuli/stimuli.txt", "stimuli/expected_response.txt")