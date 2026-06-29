// Compact closed-loop AMCP motor-control PID demo.
// Testbench plant measures real AMCP PWM output and drives external QEN GPIO.
// Firmware reads QEN_POSITION and updates PWM_DUTY using fixed-point control.

#include <stdint.h>

#include "uart.h"
#include "print.h"
#include "util.h"
#include "config.h"

#ifndef QEN_CTRL_OFFSET
#define QEN_CTRL_OFFSET             0x040u
#define QEN_STATUS_OFFSET           0x044u
#define QEN_POSITION_OFFSET         0x048u
#define QEN_ERROR_COUNT_OFFSET      0x058u
#define QEN_SAMPLE_PERIOD_OFFSET    0x05cu
#endif

#define QEN_EN               (1u << 0)
#define QEN_CLR_POS          (1u << 1)
#define QEN_CLR_ERR          (1u << 2)

#define QEN_MODE_MOTOR_PLANT 0x515EC10Du

#define PWM_PERIOD_COUNTS    100u
#define DUTY_MIN             0
#define DUTY_MAX             100
#define DUTY_BIAS            50

#define TARGET_POS           120

#define CONTROL_STEPS        48
#define TRACE_N              32
#define CONTROL_WAIT_CYCLES  2600u

// Q8 fixed-point gains.
#define Q8                   8
#define KP_Q8                64
#define KI_Q8                2
#define KD_Q8                128

#define INTEGRAL_LIMIT       2000

#define R(off)               (*reg32(AMCP_BASE_ADDR, (off)))

static uint32_t fail;

// Compact trace storage.
static uint8_t tr_k[TRACE_N];
static int16_t tr_pos[TRACE_N];
static int16_t tr_vel[TRACE_N];
static int16_t tr_duty[TRACE_N];
static int16_t tr_int[TRACE_N];
static uint8_t tr_qerr[TRACE_N];

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

static void setup_pwm(void) {
    R(PWM_CTRL_OFFSET) = 0u;

    R(PWM_PERIOD_OFFSET) = PWM_PERIOD_COUNTS;
    R(PWM_DUTY_OFFSET)   = DUTY_BIAS;

    // Route AMCP PWM to GPIO0.
    R(AMCP_PINMUX_OFFSET) = 0x1u;

    R(PWM_STATUS_OFFSET) = 0x3u;
    R(PWM_CTRL_OFFSET) = 0x1u;
}

static void setup_qen_external_motor_plant(void) {
    R(QEN_SAMPLE_PERIOD_OFFSET) = QEN_MODE_MOTOR_PLANT;

    // External GPIO mode, not QEN_SIM_INPUT.
    R(QEN_CTRL_OFFSET) = QEN_EN | QEN_CLR_POS | QEN_CLR_ERR;
    wait_cycles(64);

    R(QEN_CTRL_OFFSET) = QEN_EN;
    wait_cycles(64);
}

static int32_t pid_step(
    int32_t target,
    int32_t pos,
    int32_t vel,
    int32_t *integral_state
) {
    int32_t error = target - pos;
    int32_t abs_error = iabs32(error);

    // Fine trim region:
    // Near the setpoint, use small commands around neutral duty.
    // This avoids coarse overshoot due to encoder quantization and plant delay.
    if (abs_error <= 12) {
        if (error > 1) {
            return 58;
        }

        if (error < -1) {
            return 42;
        }

        return DUTY_BIAS;
    }

    int32_t u_q8 =
        (DUTY_BIAS << Q8) +
        KP_Q8 * error +
        KI_Q8 * (*integral_state) -
        KD_Q8 * vel;

    int32_t duty = clamp_i32(u_q8 >> Q8, DUTY_MIN, DUTY_MAX);

    uint32_t sat_high = (duty >= DUTY_MAX) && (error > 0);
    uint32_t sat_low  = (duty <= DUTY_MIN) && (error < 0);

    if (!sat_high && !sat_low) {
        int32_t integ = *integral_state + error;
        *integral_state = clamp_i32(integ, -INTEGRAL_LIMIT, INTEGRAL_LIMIT);
    }

    u_q8 =
        (DUTY_BIAS << Q8) +
        KP_Q8 * error +
        KI_Q8 * (*integral_state) -
        KD_Q8 * vel;

    duty = clamp_i32(u_q8 >> Q8, DUTY_MIN, DUTY_MAX);
    return duty;
}

int main(void) {
    uart_init();

    fail = 0u;

    if (R(AMCP_ID_OFFSET) != 0x414D4350u) {
        return 1u;
    }

    setup_pwm();
    setup_qen_external_motor_plant();

    int32_t integral = 0;
    int32_t prev_pos = (int32_t)R(QEN_POSITION_OFFSET);
    int32_t duty = DUTY_BIAS;

    int32_t min_abs_error = iabs32(TARGET_POS - prev_pos);

    uint32_t duty_changed = 0u;
    uint32_t pos_moved = 0u;
    uint32_t got_close = 0u;
    uint32_t qerr_seen = 0u;

    uint32_t bad_integral_live = 0u;
    uint32_t bad_integral_trace = 0u;
    int32_t max_abs_integral_live = 0;

    uint32_t trace_idx = 0u;

    for (uint32_t k = 0; k < CONTROL_STEPS; k++) {
        int32_t pos = (int32_t)R(QEN_POSITION_OFFSET);
        int32_t vel = pos - prev_pos;
        int32_t err = TARGET_POS - pos;

        int32_t next_duty = pid_step(TARGET_POS, pos, vel, &integral);

        if (next_duty != duty) {
            duty_changed = 1u;
        }

        duty = next_duty;
        R(PWM_DUTY_OFFSET) = (uint32_t)duty;

        uint32_t qerr = R(QEN_ERROR_COUNT_OFFSET);

        if (qerr != 0u) {
            qerr_seen = 1u;
        }

        int32_t abs_err = iabs32(err);

        if (abs_err < min_abs_error) {
            min_abs_error = abs_err;
        }

        if (pos != 0) {
            pos_moved = 1u;
        }

        if (abs_err <= 2) {
            got_close = 1u;
        }

        int32_t abs_integral = iabs32(integral);
        if (abs_integral > max_abs_integral_live) {
            max_abs_integral_live = abs_integral;
        }

        if (abs_integral > INTEGRAL_LIMIT) {
            bad_integral_live = 1u;
        }

        uint32_t selected =
            (k < 8u) ||
            ((k >= 14u) && (k <= 32u)) ||
            (k == (CONTROL_STEPS - 1u));

        if (selected && (trace_idx < TRACE_N)) {
            tr_k[trace_idx]    = (uint8_t)k;
            tr_pos[trace_idx]  = (int16_t)pos;
            tr_vel[trace_idx]  = (int16_t)vel;
            tr_duty[trace_idx] = (int16_t)duty;
            tr_int[trace_idx]  = (int16_t)integral;
            tr_qerr[trace_idx] = (uint8_t)qerr;
            trace_idx++;
        }

        prev_pos = pos;

        wait_cycles(CONTROL_WAIT_CYCLES);
    }

    int32_t final_pos = (int32_t)R(QEN_POSITION_OFFSET);
    int32_t final_err = TARGET_POS - final_pos;
    uint32_t final_qerr = R(QEN_ERROR_COUNT_OFFSET);
    uint32_t final_close = (iabs32(final_err) <= 2);

    // Stop plant before UART printing.
    R(QEN_CTRL_OFFSET) = 0u;
    R(PWM_CTRL_OFFSET) = 0u;
    R(AMCP_PINMUX_OFFSET) = 0u;

    wait_cycles(1000);

    for (uint32_t j = 0; j < trace_idx; j++) {
        int32_t ti = (int32_t)tr_int[j];
        if (iabs32(ti) > INTEGRAL_LIMIT) {
            bad_integral_trace = 1u;
        }
    }

    // Short, safe CSV. Hex two's-complement for signed values.
    // M line excludes integral to keep printf argument count low.
    // I line prints integral separately, so the integral is still visible.
    printf("D,%x,%x,%x\n", bad_integral_live, bad_integral_trace, (uint32_t)max_abs_integral_live);
    printf("T,k,p,v,d,i,q\n");

    for (uint32_t j = 0; j < trace_idx; j++) {
        printf("T,%x,%x,%x,%x,%x,%x\n",
               (uint32_t)tr_k[j],
               (uint32_t)(int32_t)tr_pos[j],
               (uint32_t)(int32_t)tr_vel[j],
               (uint32_t)(int32_t)tr_duty[j],
               (uint32_t)(int32_t)tr_int[j],
               (uint32_t)tr_qerr[j]);
    }

    printf("S0,%x,%x,%x,%x\n",
           (uint32_t)TARGET_POS,
           (uint32_t)final_pos,
           (uint32_t)final_err,
           (uint32_t)min_abs_error);

    printf("S1,%x,%x,%x,%x,%x,%x\n",
           duty_changed,
           pos_moved,
           got_close,
           qerr_seen,
           final_qerr,
           final_close);

    check(0x10u, duty_changed != 0u);
    check(0x11u, pos_moved != 0u);
    check(0x12u, got_close != 0u);
    check(0x13u, qerr_seen == 0u);
    check(0x14u, final_qerr == 0u);
    check(0x15u, final_close != 0u);

    uart_write_flush();

    return fail;
}
