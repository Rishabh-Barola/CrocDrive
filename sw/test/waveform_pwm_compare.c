// PWM waveform comparison test.
// Generates first a software-bit-banged GPIO PWM, then hardware AMCP PWM.
// Use GTKWave to compare gpio_o[0] in the two marked regions.
//
// gpio[0] = PWM output
// gpio[1] = software-PWM marker
// gpio[2] = hardware-PWM marker

#include <stdint.h>

#include "uart.h"
#include "print.h"
#include "util.h"
#include "config.h"
#include "gpio.h"

#define GPIO0_MASK 0x1u
#define GPIO1_MASK 0x2u
#define GPIO2_MASK 0x4u

static inline uint32_t read_mcycle(void) {
    uint32_t value;
    asm volatile ("csrr %0, mcycle" : "=r"(value));
    return value;
}

static inline int cycle_before(uint32_t now, uint32_t deadline) {
    return ((int32_t)(now - deadline)) < 0;
}

static void wait_until_cycle(uint32_t deadline) {
    while (cycle_before(read_mcycle(), deadline)) {
        asm volatile ("nop");
    }
}

static void delay_cycles(uint32_t cycles) {
    uint32_t start = read_mcycle();
    wait_until_cycle(start + cycles);
}

static void release_gpio0_from_amcp(void) {
    *reg32(AMCP_BASE_ADDR, PWM_CTRL_OFFSET) = 0x0;
    *reg32(AMCP_BASE_ADDR, AMCP_PINMUX_OFFSET) = 0x0;
}

static void setup_normal_gpio_outputs(void) {
    release_gpio0_from_amcp();

    gpio_set_direction(GPIO0_MASK | GPIO1_MASK | GPIO2_MASK,
                       GPIO0_MASK | GPIO1_MASK | GPIO2_MASK);

    gpio_enable(GPIO0_MASK | GPIO1_MASK | GPIO2_MASK);
    gpio_write(0x0);
}

static void software_pwm_periods(uint32_t periods,
                                 uint32_t high_cycles,
                                 uint32_t low_cycles) {
    volatile uint32_t *gpio_toggle_reg = reg32(GPIO_BASE_ADDR, GPIO_TOGGLE_REG_OFFSET);

    setup_normal_gpio_outputs();

    // Mark software PWM region.
    gpio_pin_set(1);
    gpio_pin_clear(2);

    for (uint32_t i = 0; i < periods; i++) {
        uint32_t t0;

        // Low -> high
        t0 = read_mcycle();
        *gpio_toggle_reg = GPIO0_MASK;
        wait_until_cycle(t0 + high_cycles);

        // High -> low
        t0 = read_mcycle();
        *gpio_toggle_reg = GPIO0_MASK;
        wait_until_cycle(t0 + low_cycles);
    }

    gpio_pin_clear(0);
    gpio_pin_clear(1);
}

static void hardware_pwm_run(uint32_t period,
                             uint32_t duty,
                             uint32_t run_cycles) {
    // Mark hardware PWM region using GPIO2.
    gpio_pin_clear(1);
    gpio_pin_set(2);

    *reg32(AMCP_BASE_ADDR, PWM_CTRL_OFFSET) = 0x0;

    *reg32(AMCP_BASE_ADDR, PWM_PERIOD_OFFSET) = period;
    *reg32(AMCP_BASE_ADDR, PWM_DUTY_OFFSET)   = duty;

    // Route AMCP PWM to gpio[0].
    *reg32(AMCP_BASE_ADDR, AMCP_PINMUX_OFFSET) = 0x1;

    // Clear sticky status.
    *reg32(AMCP_BASE_ADDR, PWM_STATUS_OFFSET) = 0x3;

    // Enable PWM.
    *reg32(AMCP_BASE_ADDR, PWM_CTRL_OFFSET) = 0x1;

    delay_cycles(run_cycles);

    *reg32(AMCP_BASE_ADDR, PWM_CTRL_OFFSET) = 0x0;
    *reg32(AMCP_BASE_ADDR, AMCP_PINMUX_OFFSET) = 0x0;

    gpio_pin_clear(2);
    gpio_pin_clear(0);
}

int main(void) {
    uart_init();

    printf("PWM waveform compare start\n");

    uint32_t id = *reg32(AMCP_BASE_ADDR, AMCP_ID_OFFSET);
    printf("AMCP ID: 0x%x\n", id);

    if (id != 0x414D4350) {
        printf("AMCP ID mismatch\n");
        uart_write_flush();
        return 1;
    }

    // Keep this short to make GTKWave easy.
    // Software phase: attempts 10-cycle PWM, but overhead will be visible.
    software_pwm_periods(20, 3, 7);

    // Gap between regions.
    delay_cycles(100);

    // Hardware phase: exact period=10, duty=3 PWM for 300 cycles.
    hardware_pwm_run(10, 3, 300);

    printf("PWM waveform compare done\n");

    uart_write_flush();
    return 0;
}