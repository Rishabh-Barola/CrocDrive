// Software PWM power workload.
// CPU bit-bangs GPIO0 in a tight loop.
// Used as a baseline against AMCP hardware PWM offload.

#include <stdint.h>

#include "util.h"
#include "config.h"
#include "gpio.h"

#define GPIO0_MASK 0x1u

#define GPIO_POWER_MARKER 7u
#define GPIO_POWER_MASK   (1u << GPIO_POWER_MARKER)
#define R(off) (*reg32(AMCP_BASE_ADDR, (off)))

static volatile uint32_t sink = 1u;

int main(void) {
    if (R(AMCP_ID_OFFSET) != 0x414D4350u) {
        return 1u;
    }

    // Ensure AMCP does not drive GPIO0.
    R(PWM_CTRL_OFFSET) = 0u;
    R(AMCP_PINMUX_OFFSET) = 0u;

    gpio_set_direction(GPIO0_MASK | GPIO_POWER_MASK, GPIO0_MASK | GPIO_POWER_MASK);
    gpio_enable(GPIO0_MASK | GPIO_POWER_MASK);
    gpio_write(0u);

    // Mark the start of the real software-PWM workload for VCD power analysis.
    gpio_pin_set(GPIO_POWER_MARKER);

    volatile uint32_t *gpio_toggle = reg32(GPIO_BASE_ADDR, GPIO_TOGGLE_REG_OFFSET);

    for (uint32_t k = 0u; k < 300000u; k++) {
        *gpio_toggle = GPIO0_MASK;

        sink = sink * 1664525u + 1013904223u;
        sink ^= sink >> 16;

        asm volatile ("nop");
        asm volatile ("nop");

        *gpio_toggle = GPIO0_MASK;

        sink = sink * 22695477u + 1u;
        sink ^= sink >> 13;

        asm volatile ("nop");
        asm volatile ("nop");
    }

    gpio_pin_clear(GPIO_POWER_MARKER);
    gpio_write(0u);

    return 0u;
}
