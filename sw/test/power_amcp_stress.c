// Power workload for AMCP upgrade.
// Stresses hardware PWM, QEN simulation-input path, AMCP MMIO reads/writes,
// and control-like integer computation.
//
// This is intended for post-layout VCD-based power analysis.
// No UART printing: avoids UART activity dominating the power window.

#include <stdint.h>

#include "util.h"
#include "config.h"
#include "gpio.h"

#ifndef QEN_CTRL_OFFSET
#define QEN_CTRL_OFFSET             0x040u
#define QEN_STATUS_OFFSET           0x044u
#define QEN_POSITION_OFFSET         0x048u
#define QEN_VELOCITY_OFFSET         0x04cu
#define QEN_DELTA_OFFSET            0x050u
#define QEN_ERROR_COUNT_OFFSET      0x058u
#define QEN_SAMPLE_PERIOD_OFFSET    0x05cu
#define QEN_SIM_INPUT_OFFSET        0x060u
#endif

#define QEN_EN        (1u << 0)
#define QEN_CLR_POS   (1u << 1)
#define QEN_CLR_ERR   (1u << 2)
#define QEN_SIM       (1u << 4)

#define PWM_PERIOD_COUNTS 100u

#define GPIO_POWER_MARKER 7u
#define GPIO_POWER_MASK   (1u << GPIO_POWER_MARKER)

#define R(off) (*reg32(AMCP_BASE_ADDR, (off)))

static volatile uint32_t sink = 1u;

static int32_t clamp_i32(int32_t x, int32_t lo, int32_t hi) {
    if (x < lo) return lo;
    if (x > hi) return hi;
    return x;
}

static void wait_cycles(uint32_t n) {
    for (volatile uint32_t i = 0; i < n; i++) {
        asm volatile ("nop");
    }
}

static void setup_pwm(void) {
    R(PWM_CTRL_OFFSET) = 0u;
    R(PWM_PERIOD_OFFSET) = PWM_PERIOD_COUNTS;
    R(PWM_DUTY_OFFSET) = 50u;
    R(AMCP_PINMUX_OFFSET) = 0x1u;
    R(PWM_STATUS_OFFSET) = 0x3u;
    R(PWM_CTRL_OFFSET) = 0x1u;
}

static void setup_qen_sim(void) {
    R(QEN_SIM_INPUT_OFFSET) = 0u;
    R(QEN_SAMPLE_PERIOD_OFFSET) = 64u;

    R(QEN_CTRL_OFFSET) = QEN_EN | QEN_SIM | QEN_CLR_POS | QEN_CLR_ERR;
    wait_cycles(32);

    R(QEN_CTRL_OFFSET) = QEN_EN | QEN_SIM;
    wait_cycles(32);
}

static void write_qen_ab(uint32_t ab) {
    uint32_t a = ab & 1u;
    uint32_t b = (ab >> 1) & 1u;
    R(QEN_SIM_INPUT_OFFSET) = a | (b << 1);
}

int main(void) {
    if (R(AMCP_ID_OFFSET) != 0x414D4350u) {
        return 1u;
    }

    setup_pwm();
    setup_qen_sim();

    gpio_set_direction(GPIO_POWER_MASK, GPIO_POWER_MASK);
    gpio_enable(GPIO_POWER_MASK);
    gpio_pin_clear(GPIO_POWER_MARKER);

    uint32_t duty = 0u;

    // Mark the start of the real workload for VCD-based power analysis.
    gpio_pin_set(GPIO_POWER_MARKER);
    int32_t integral = 0;

    for (uint32_t k = 0u; k < 200000u; k++) {
        // Sweep PWM duty through all 1% levels.
        if ((k & 0x1fu) == 0u) {
            duty++;
            if (duty > 100u) {
                duty = 0u;
            }
            R(PWM_DUTY_OFFSET) = duty;
        }

        // Drive QEN simulation input through legal quadrature transitions.
        if ((k & 0x7u) == 0u) {
            uint32_t phase = (k >> 3) & 0x3u;
            uint32_t ab;

            if (phase == 0u) {
                ab = 1u;      // 01
            } else if (phase == 1u) {
                ab = 3u;      // 11
            } else if (phase == 2u) {
                ab = 2u;      // 10
            } else {
                ab = 0u;      // 00
            }

            write_qen_ab(ab);
        }

        // Controller-like integer workload.
        int32_t target_mv = ((k & 0x400u) != 0u) ? 700 : 420;
        int32_t measured_mv = (int32_t)duty * 12;
        int32_t err = target_mv - measured_mv;

        integral += err;
        integral = clamp_i32(integral, -2000, 2000);

        int32_t ctrl = 58 + (err >> 5) + (integral >> 9);
        ctrl = clamp_i32(ctrl, 0, 100);

        if ((k & 0x3fu) == 0u) {
            R(PWM_DUTY_OFFSET) = (uint32_t)ctrl;
        }

        // Periodic AMCP readback activity.
        if ((k & 0xffu) == 0u) {
            sink ^= R(PWM_COUNTER_OFFSET);
            sink += R(PWM_STATUS_OFFSET);
            sink ^= R(QEN_POSITION_OFFSET);
            sink += R(QEN_VELOCITY_OFFSET);
            sink ^= R(QEN_DELTA_OFFSET);
            sink += R(QEN_ERROR_COUNT_OFFSET);
        }

        sink = sink * 1664525u + 1013904223u;
        sink ^= sink >> 16;
    }

    gpio_pin_clear(GPIO_POWER_MARKER);

    R(PWM_CTRL_OFFSET) = 0u;
    R(QEN_CTRL_OFFSET) = 0u;
    R(AMCP_PINMUX_OFFSET) = 0u;

    return 0u;
}
