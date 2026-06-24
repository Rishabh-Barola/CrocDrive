// AMCP/PWM benchmark.
// Compares CPU-driven software PWM against hardware AMCP PWM.
//
// Test A:
//   CPU cycles required to generate N PWM periods in software
//   versus CPU cycles required to configure hardware PWM once.
//
// Test B:
//   CPU useful work available while hardware PWM runs
//   versus CPU occupation during software PWM generation.

#include <stdint.h>

#include "uart.h"
#include "print.h"
#include "util.h"
#include "config.h"
#include "gpio.h"

#define GPIO0_MASK 0x1u

static volatile uint32_t benchmark_sink = 0;

static inline uint32_t read_mcycle(void) {
    uint32_t value;
    asm volatile ("csrr %0, mcycle" : "=r"(value));
    return value;
}

static inline void delay_nops(uint32_t n) {
    for (volatile uint32_t i = 0; i < n; i++) {
        asm volatile ("nop");
    }
}

static inline int cycle_before(uint32_t now, uint32_t deadline) {
    return ((int32_t)(now - deadline)) < 0;
}

static void wait_until_cycle(uint32_t deadline) {
    while (cycle_before(read_mcycle(), deadline)) {
        asm volatile ("nop");
    }
}

static void release_gpio0_from_amcp(void) {
    // Disable hardware PWM and release GPIO0 back to normal GPIO.
    *reg32(AMCP_BASE_ADDR, PWM_CTRL_OFFSET) = 0x0;
    *reg32(AMCP_BASE_ADDR, AMCP_PINMUX_OFFSET) = 0x0;
}

static void setup_gpio0_for_software_pwm(void) {
    release_gpio0_from_amcp();

    gpio_pin_set_output(0);
    gpio_pin_enable(0);
    gpio_pin_clear(0);
}

static uint32_t measure_software_pwm_cycles(
    uint32_t num_periods,
    uint32_t high_delay_nops,
    uint32_t low_delay_nops
) {
    volatile uint32_t *gpio_toggle_reg = reg32(GPIO_BASE_ADDR, GPIO_TOGGLE_REG_OFFSET);

    setup_gpio0_for_software_pwm();

    uint32_t start = read_mcycle();

    for (uint32_t i = 0; i < num_periods; i++) {
        // Toggle low->high.
        *gpio_toggle_reg = GPIO0_MASK;
        delay_nops(high_delay_nops);

        // Toggle high->low.
        *gpio_toggle_reg = GPIO0_MASK;
        delay_nops(low_delay_nops);
        
    }

    uint32_t end = read_mcycle();

    gpio_pin_clear(0);

    return end - start;
}

static uint32_t measure_hardware_pwm_config_cycles(
    uint32_t period,
    uint32_t duty
) {
    // Start from disabled state.
    *reg32(AMCP_BASE_ADDR, PWM_CTRL_OFFSET) = 0x0;

    uint32_t start = read_mcycle();

    *reg32(AMCP_BASE_ADDR, PWM_PERIOD_OFFSET) = period;
    *reg32(AMCP_BASE_ADDR, PWM_DUTY_OFFSET)   = duty;

    // Route AMCP PWM to GPIO0.
    *reg32(AMCP_BASE_ADDR, AMCP_PINMUX_OFFSET) = 0x1;

    // Clear sticky status flags.
    *reg32(AMCP_BASE_ADDR, PWM_STATUS_OFFSET) = 0x3;

    // Enable PWM, active-high.
    *reg32(AMCP_BASE_ADDR, PWM_CTRL_OFFSET) = 0x1;

    uint32_t end = read_mcycle();

    return end - start;
}

static uint32_t useful_work_until(uint32_t window_cycles) {
    uint32_t start = read_mcycle();
    uint32_t deadline = start + window_cycles;

    uint32_t count = 0;
    uint32_t acc = benchmark_sink + 1;

    while (cycle_before(read_mcycle(), deadline)) {
        // Some cheap integer work that should not be optimized away.
        acc = acc * 1664525u + 1013904223u;
        acc ^= (acc >> 16);
        count++;
    }

    benchmark_sink = acc;
    return count;
}

static uint32_t software_pwm_until(
    uint32_t window_cycles,
    uint32_t high_cycles,
    uint32_t low_cycles
) {
    volatile uint32_t *gpio_toggle_reg = reg32(GPIO_BASE_ADDR, GPIO_TOGGLE_REG_OFFSET);

    setup_gpio0_for_software_pwm();

    uint32_t start = read_mcycle();
    uint32_t deadline = start + window_cycles;
    uint32_t periods = 0;

    while (cycle_before(read_mcycle(), deadline)) {
        uint32_t t_high_start = read_mcycle();

        // Low -> high
        *gpio_toggle_reg = GPIO0_MASK;
        wait_until_cycle(t_high_start + high_cycles);

        uint32_t t_low_start = read_mcycle();

        // High -> low
        *gpio_toggle_reg = GPIO0_MASK;
        wait_until_cycle(t_low_start + low_cycles);

        periods++;
    }

    gpio_pin_clear(0);

    return periods;
}

static void run_test_a(void) {
    const uint32_t period = 10;
    const uint32_t duty = 3;

    // These are software delay knobs, not exact final waveform cycles.
    // MMIO write overhead dominates for such a small period.
    const uint32_t high_delay_nops = 3;
    const uint32_t low_delay_nops = 7;

  
    
    static const uint32_t n_values[4] = {10, 100, 1000, 10000};
    printf("TEST_A_CPU_CYCLES\n");
    
    printf("N_hex,sw_cycles_hex,sw_cycles_per_period_hex,hw_cfg_cycles_hex,offload_x100_hex\n");
    for (uint32_t i = 0; i < 4; i++) {
        uint32_t n = n_values[i];

        uint32_t sw_cycles = measure_software_pwm_cycles(
            n,
            high_delay_nops,
            low_delay_nops
        );

        uint32_t hw_cfg_cycles = measure_hardware_pwm_config_cycles(
            period,
            duty
        );

        uint32_t sw_per_period = sw_cycles / n;
        uint32_t offload_x100 = 0;

        if (hw_cfg_cycles != 0) {
            offload_x100 = (sw_cycles / hw_cfg_cycles) * 100u;
        }

        printf("A,0x%x,0x%x,0x%x,0x%x,0x%x\n",
       n,
       sw_cycles,
       sw_per_period,
       hw_cfg_cycles,
       offload_x100);
    }
}

static void run_test_b(void) {
    const uint32_t period = 10;
    const uint32_t duty = 3;

    const uint32_t window_cycles = 100000;

    printf("TEST_B_CPU_AVAILABILITY\n");
    
    printf("window_cycles_hex,hw_expected_pwm_periods_hex,hw_useful_iters_hex,sw_pwm_periods_in_window_hex,sw_useful_iters_hex\n");
    // Hardware PWM mode:
    // Configure once, then CPU is free to do useful work.
    measure_hardware_pwm_config_cycles(period, duty);

    uint32_t hw_useful_iters = useful_work_until(window_cycles);
    uint32_t hw_expected_pwm_periods = window_cycles / period;

    // Software PWM mode:
    // CPU is occupied toggling GPIO, so useful work is effectively zero.
    uint32_t sw_periods = software_pwm_until(
        window_cycles,
        duty,
        period - duty
    );

    uint32_t sw_useful_iters = 0;

    printf("B,0x%x,0x%x,0x%x,0x%x,0x%x\n",
       window_cycles,
       hw_expected_pwm_periods,
       hw_useful_iters,
       sw_periods,
       sw_useful_iters);
}

int main(void) {
    uart_init();

    printf("PWM benchmark start\n");

    uint32_t id = *reg32(AMCP_BASE_ADDR, AMCP_ID_OFFSET);
    printf("AMCP ID: 0x%x\n", id);

    if (id != 0x414D4350) {
        printf("AMCP ID mismatch\n");
        uart_write_flush();
        return 1;
    }

    run_test_a();
    run_test_b();

    printf("PWM benchmark done\n");

    uart_write_flush();
    return 0;
}