// Stable closed-loop AMCP buck-converter PID demo.
//
// Hardware contribution:
//   AMCP PWM autonomously generates 1 MHz PWM on GPIO0.
//   Firmware only updates PWM_DUTY; it does not bit-bang PWM.
//
// Testbench contribution:
//   Observes real GPIO0 PWM.
//   Simulates averaged buck-converter Vout.
//   Drives fake 10-bit ADC feedback on GPIO[8:17].
//
// GPIO0      = AMCP PWM output
// GPIO5      = buck PID active marker
// GPIO6      = PWM resolution sweep marker
// GPIO[8:17] = fake 10-bit ADC input from testbench

#include <stdint.h>

#include "util.h"
#include "config.h"
#include "gpio.h"

#define R(off) (*reg32(AMCP_BASE_ADDR, (off)))

#define VIN_MV              1200u
#define TARGET_MV           700u

// 100 MHz / 100 = 1 MHz PWM.
// period=100 gives 1% duty resolution.
#define PWM_PERIOD_COUNTS   100u

#define DUTY_MIN            0
#define DUTY_MAX            100

#define GPIO_PID_MARKER     5u
#define GPIO_RES_MARKER     6u
#define GPIO_PID_MASK       (1u << GPIO_PID_MARKER)
#define GPIO_RES_MASK       (1u << GPIO_RES_MARKER)

#define ADC_SHIFT           8u
#define ADC_MASK            (0x3ffu << ADC_SHIFT)

// Keep simulation short.
#define CONTROL_STEPS       120u
#define CONTROL_WAIT_CYCLES 800u

// Q8 fixed-point gains.
// This is deliberately conservative because the testbench buck plant is fast.
#define Q8                  8
#define KP_Q8               1
#define KI_Q8               1
#define KD_Q8               8
#define INTEGRAL_LIMIT      300

#define MAX_DUTY_STEP       1

static uint32_t fail;

static int32_t iabs32(int32_t x) {
    return (x < 0) ? -x : x;
}

static int32_t clamp_i32(int32_t x, int32_t lo, int32_t hi) {
    if (x < lo) {
        return lo;
    }

    if (x > hi) {
        return hi;
    }

    return x;
}

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

static uint32_t read_adc_code(void) {
    return (gpio_read() & ADC_MASK) >> ADC_SHIFT;
}

static int32_t read_adc_mv(void) {
    uint32_t code = read_adc_code();

    // 10-bit ADC: 0..1023 maps to 0..VIN_MV.
    return (int32_t)((code * VIN_MV + 511u) / 1023u);
}

static void setup_gpio_for_buck_pid(void) {
    // GPIO5 and GPIO6 are firmware-driven markers.
    gpio_set_direction(GPIO_PID_MASK | GPIO_RES_MASK,
                       GPIO_PID_MASK | GPIO_RES_MASK);
    gpio_enable(GPIO_PID_MASK | GPIO_RES_MASK);

    gpio_pin_clear(GPIO_PID_MARKER);
    gpio_pin_clear(GPIO_RES_MARKER);

    // GPIO[8:17] are ADC feedback inputs driven by testbench.
    gpio_set_direction(ADC_MASK, 0u);
    gpio_enable(ADC_MASK);
}

static void setup_pwm(uint32_t duty) {
    R(PWM_CTRL_OFFSET) = 0u;

    R(PWM_PERIOD_OFFSET) = PWM_PERIOD_COUNTS;
    R(PWM_DUTY_OFFSET)   = duty;

    // Route AMCP PWM to GPIO0.
    R(AMCP_PINMUX_OFFSET) = 0x1u;

    // Clear sticky PWM flags.
    R(PWM_STATUS_OFFSET) = 0x3u;

    // Enable PWM.
    R(PWM_CTRL_OFFSET) = 0x1u;
}

static void run_resolution_sweep(void) {
    gpio_pin_set(GPIO_RES_MARKER);

    for (uint32_t duty = 0u; duty <= PWM_PERIOD_COUNTS; duty++) {
        R(PWM_DUTY_OFFSET) = duty;

        // Hold long enough for testbench to observe each duty level.
        wait_cycles(1000u);
    }

    gpio_pin_clear(GPIO_RES_MARKER);
    wait_cycles(1000u);
}

static int32_t pid_compute_target_duty(
    int32_t target_mv,
    int32_t vout_mv,
    int32_t dv_mv,
    int32_t *integral_state
) {
    int32_t err_mv = target_mv - vout_mv;
    int32_t abs_err_mv = iabs32(err_mv);

    // Ideal buck feed-forward:
    // duty ≈ Vout / Vin.
    int32_t duty_ff = (target_mv * 100 + ((int32_t)VIN_MV / 2)) / (int32_t)VIN_MV;

    // Only integrate close to the target. This prevents wind-up while ramping.
    if (abs_err_mv <= 36) {
        int32_t integ = *integral_state + err_mv;
        *integral_state = clamp_i32(integ, -INTEGRAL_LIMIT, INTEGRAL_LIMIT);
    }

    int32_t correction_q8 =
        KP_Q8 * err_mv +
        KI_Q8 * (*integral_state) -
        KD_Q8 * dv_mv;

    int32_t duty = duty_ff + (correction_q8 >> Q8);
    return clamp_i32(duty, DUTY_MIN, DUTY_MAX);
}

static int32_t slew_limit_duty(int32_t current, int32_t target) {
    int32_t delta = target - current;

    if (delta > MAX_DUTY_STEP) {
        delta = MAX_DUTY_STEP;
    } else if (delta < -MAX_DUTY_STEP) {
        delta = -MAX_DUTY_STEP;
    }

    return clamp_i32(current + delta, DUTY_MIN, DUTY_MAX);
}

int main(void) {
    fail = 0u;

    if (R(AMCP_ID_OFFSET) != 0x414D4350u) {
        return 1u;
    }

    setup_gpio_for_buck_pid();

    // Start PWM at 0% duty.
    setup_pwm(0u);

    // First prove 1% resolution at 1 MHz.
    run_resolution_sweep();

    // The resolution sweep ends at 100% duty. Reset to 0% before starting
    // closed-loop control so the plant does not see an artificial full-scale kick.
    R(PWM_DUTY_OFFSET) = 0u;
    wait_cycles(2000u);

    // Closed-loop PID run.
    gpio_pin_set(GPIO_PID_MARKER);

    int32_t integral = 0;
    int32_t prev_vout_mv = read_adc_mv();
    int32_t duty = 0;

    uint32_t duty_changed = 0u;
    uint32_t got_close = 0u;
    uint32_t reached_target_band = 0u;

    int32_t min_abs_err = iabs32((int32_t)TARGET_MV - prev_vout_mv);

    for (uint32_t k = 0u; k < CONTROL_STEPS; k++) {
        int32_t vout_mv = read_adc_mv();
        int32_t dv_mv   = vout_mv - prev_vout_mv;
        int32_t err_mv  = (int32_t)TARGET_MV - vout_mv;

        int32_t target_duty = pid_compute_target_duty(
            (int32_t)TARGET_MV,
            vout_mv,
            dv_mv,
            &integral
        );

        int32_t next_duty = slew_limit_duty(duty, target_duty);

        if (next_duty != duty) {
            duty_changed = 1u;
        }

        duty = next_duty;
        R(PWM_DUTY_OFFSET) = (uint32_t)duty;

        int32_t abs_err = iabs32(err_mv);

        if (abs_err < min_abs_err) {
            min_abs_err = abs_err;
        }

        if (abs_err <= 25) {
            got_close = 1u;
        }

        if (abs_err <= 15) {
            reached_target_band = 1u;
        }

        prev_vout_mv = vout_mv;

        wait_cycles(CONTROL_WAIT_CYCLES);
    }

    // Let the plant and ADC feedback settle for a few extra control intervals
    // while the marker is still high. This gives a clean final sample.
    for (uint32_t k = 0u; k < 8u; k++) {
        wait_cycles(CONTROL_WAIT_CYCLES);
    }

    int32_t final_vout_mv = read_adc_mv();
    int32_t final_err_mv  = (int32_t)TARGET_MV - final_vout_mv;
    uint32_t final_close  = (iabs32(final_err_mv) <= 15);

    // Tell the testbench to stop observing the closed-loop plant, but keep PWM
    // alive briefly so any in-progress 100-cycle PWM measurement completes
    // without seeing an artificial PWM-off transient.
    gpio_pin_clear(GPIO_PID_MARKER);
    wait_cycles(3000u);

    R(PWM_CTRL_OFFSET) = 0u;
    R(AMCP_PINMUX_OFFSET) = 0u;

    check(0x10u, duty_changed != 0u);
    check(0x11u, got_close != 0u);
    check(0x12u, reached_target_band != 0u);
    check(0x13u, final_close != 0u);

    return fail;
}
