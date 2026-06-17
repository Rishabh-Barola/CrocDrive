import random

def write_vec(f, polarity, period, duty, samples):
    # Format:
    # polarity[0] period[15:0] duty[15:0] samples[15:0]
    line = f"{polarity:01b}{period:016b}{duty:016b}{samples:016b}"
    f.write(line + "\n")

def generate_test_vectors(filename, num_random=50):
    random.seed(1)

    with open(filename, "w") as f:
        # Directed tests
        write_vec(f, polarity=0, period=10, duty=3,  samples=25)  # normal active-high
        write_vec(f, polarity=0, period=8,  duty=0,  samples=18)  # always low
        write_vec(f, polarity=0, period=8,  duty=8,  samples=18)  # always high
        write_vec(f, polarity=0, period=8,  duty=12, samples=18)  # clamp duty to period
        write_vec(f, polarity=1, period=8,  duty=2,  samples=18)  # active-low
        write_vec(f, polarity=0, period=1,  duty=1,  samples=8)   # shortest valid period
        write_vec(f, polarity=0, period=0,  duty=3,  samples=8)   # invalid period

        # Random tests
        for _ in range(num_random):
            period = random.randint(0, 64)
            duty = random.randint(0, 80)
            polarity = random.randint(0, 1)

            if period == 0:
                samples = 8
            else:
                samples = min(200, 2 * period + 5)

            write_vec(f, polarity, period, duty, samples)

if __name__ == "__main__":
    generate_test_vectors("stimuli/stimuli.txt", num_random=100)