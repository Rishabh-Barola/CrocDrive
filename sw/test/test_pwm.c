// Basic AMCP/PWM test.
// Configures PWM at AMCP_BASE_ADDR and routes PWM output to gpio[0].

#include <stdint.h>

#include "uart.h"
#include "print.h"
#include "util.h"
#include "config.h"

int main(void) {
    uart_init();

    uint32_t id = *reg32(AMCP_BASE_ADDR, AMCP_ID_OFFSET);
    uint32_t version = *reg32(AMCP_BASE_ADDR, AMCP_VERSION_OFFSET);

    printf("AMCP ID: 0x%x\n", id);
    printf("AMCP version: 0x%x\n", version);

    if (id != 0x414D4350) {
        printf("AMCP ID mismatch\n");
        uart_write_flush();
        return 1;
    }

    // Route PWM to gpio[0].
    *reg32(AMCP_BASE_ADDR, AMCP_PINMUX_OFFSET) = 0x1;

    // Configure period=10 cycles, duty=3 cycles.
    *reg32(AMCP_BASE_ADDR, PWM_PERIOD_OFFSET) = 10;
    *reg32(AMCP_BASE_ADDR, PWM_DUTY_OFFSET)   = 3;

    // Enable PWM, active-high polarity.
    // PWM_CTRL[0] = enable
    // PWM_CTRL[1] = polarity
    *reg32(AMCP_BASE_ADDR, PWM_CTRL_OFFSET) = 0x1;

    uint32_t pinmux = *reg32(AMCP_BASE_ADDR, AMCP_PINMUX_OFFSET);
    uint32_t ctrl   = *reg32(AMCP_BASE_ADDR, PWM_CTRL_OFFSET);
    uint32_t period = *reg32(AMCP_BASE_ADDR, PWM_PERIOD_OFFSET);
    uint32_t duty   = *reg32(AMCP_BASE_ADDR, PWM_DUTY_OFFSET);

    printf("AMCP pinmux: 0x%x\n", pinmux);
    printf("PWM ctrl: 0x%x\n", ctrl);
    printf("PWM period: 0x%x\n", period);
    printf("PWM duty: 0x%x\n", duty);

    if (pinmux != 0x1 || ctrl != 0x1 || period != 10 || duty != 3) {
        printf("PWM register readback failed\n");
        uart_write_flush();
        return 1;
    }

    // Let PWM run long enough for several wraps.
    for (volatile int i = 0; i < 1000; i++) {
        asm volatile("nop");
    }

    uint32_t counter       = *reg32(AMCP_BASE_ADDR, PWM_COUNTER_OFFSET);
    uint32_t status        = *reg32(AMCP_BASE_ADDR, PWM_STATUS_OFFSET);
    uint32_t duty_active   = *reg32(AMCP_BASE_ADDR, PWM_DUTY_ACTIVE_OFFSET);
    uint32_t period_active = *reg32(AMCP_BASE_ADDR, PWM_PERIOD_ACTIVE_OFFSET);

    printf("PWM counter: 0x%x\n", counter);
    printf("PWM status: 0x%x\n", status);
    printf("PWM duty active: 0x%x\n", duty_active);
    printf("PWM period active: 0x%x\n", period_active);

    if ((status & 0x1) == 0) {
        printf("PWM period_done flag not set\n");
        uart_write_flush();
        return 1;
    }

    if (period_active != 10 || duty_active != 3) {
        printf("PWM active register mismatch\n");
        uart_write_flush();
        return 1;
    }

    printf("PWM test passed\n");

    uart_write_flush();
    return 0;
}