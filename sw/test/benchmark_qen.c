// External-GPIO AMCP/QEN scaling benchmark.
// Software path: CPU decodes N quadrature transitions in C.
// Hardware path: testbench drives N external GPIO A/B transitions while QEN tracks.
// QEN_SIM_INPUT is disabled in the hardware path.

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

#define QEN_EN          (1u << 0)
#define QEN_CLR_POS     (1u << 1)
#define QEN_CLR_ERR     (1u << 2)

#define MODE_BENCH_100   0x515E0064u
#define MODE_BENCH_400   0x515E0190u
#define MODE_BENCH_1600  0x515E0640u

#define R(off)          (*reg32(AMCP_BASE_ADDR, (off)))

static volatile uint32_t sink;

static inline uint32_t read_mcycle(void) {
    uint32_t value;
    asm volatile ("csrr %0, mcycle" : "=r"(value));
    return value;
}

static inline int cycle_before(uint32_t now, uint32_t deadline) {
    return ((int32_t)(now - deadline)) < 0;
}

static void wait_cycles(uint32_t n) {
    for (volatile uint32_t i = 0; i < n; i++) {
        asm volatile ("nop");
    }
}

static uint32_t useful_work_for(uint32_t window_cycles) {
    uint32_t start = read_mcycle();
    uint32_t deadline = start + window_cycles;

    uint32_t count = 0;
    uint32_t acc = sink + 1u;

    while (cycle_before(read_mcycle(), deadline)) {
        acc = acc * 1664525u + 1013904223u;
        acc ^= acc >> 16;
        count++;
    }

    sink = acc;
    return count;
}

static int32_t sw_pos;
static uint32_t sw_err;
static uint32_t sw_prev_ab;

static void sw_reset(void) {
    sw_pos = 0;
    sw_err = 0;
    sw_prev_ab = 0;
}

static void sw_step(uint32_t ab) {
    uint32_t t = ((sw_prev_ab & 3u) << 2) | (ab & 3u);

    switch (t) {
        case 0x1u: // 00 -> 01
        case 0x7u: // 01 -> 11
        case 0xeu: // 11 -> 10
        case 0x8u: // 10 -> 00
            sw_pos++;
            break;

        case 0x2u: // 00 -> 10
        case 0xbu: // 10 -> 11
        case 0xdu: // 11 -> 01
        case 0x4u: // 01 -> 00
            sw_pos--;
            break;

        case 0x0u:
        case 0x5u:
        case 0xau:
        case 0xfu:
            break;

        default:
            sw_err++;
            break;
    }

    sw_prev_ab = ab & 3u;
}

static uint32_t run_software_decode(uint32_t n) {
    static const uint32_t seq[4] = {1u, 3u, 2u, 0u};

    sw_reset();

    uint32_t start = read_mcycle();

    for (uint32_t i = 0; i < n; i++) {
        sw_step(seq[i & 3u]);
    }

    uint32_t end = read_mcycle();

    return end - start;
}

static uint32_t start_hardware_qen_external(uint32_t mode) {
    R(QEN_SAMPLE_PERIOD_OFFSET) = mode;

    uint32_t start = read_mcycle();

    // External GPIO mode:
    // Do NOT set QEN_SIM_INPUT_ENABLE.
    R(QEN_CTRL_OFFSET) = QEN_EN | QEN_CLR_POS | QEN_CLR_ERR;
    wait_cycles(16);

    R(QEN_CTRL_OFFSET) = QEN_EN;

    uint32_t end = read_mcycle();

    return end - start;
}

static uint32_t wait_for_hw_position(uint32_t n) {
    for (uint32_t i = 0; i < 500000u; i++) {
        if ((int32_t)R(QEN_POSITION_OFFSET) == (int32_t)n) {
            return 1u;
        }
    }

    return 0u;
}

static uint32_t run_case(uint32_t n, uint32_t mode, uint32_t fail_base) {
    uint32_t sw_cycles = run_software_decode(n);
    int32_t sw_final_pos = sw_pos;
    uint32_t sw_final_err = sw_err;

    uint32_t hw_cfg_cycles = start_hardware_qen_external(mode);

    // Give the CPU useful work while external encoder edges are being tracked.
    // The window scales with N so larger encoder streams get longer time.
    uint32_t work_window = 5000u + 16u * n;
    uint32_t useful_iters = useful_work_for(work_window);

    uint32_t reached = wait_for_hw_position(n);

    int32_t hw_final_pos = (int32_t)R(QEN_POSITION_OFFSET);
    uint32_t hw_final_err = R(QEN_ERROR_COUNT_OFFSET);

    // Disable QEN so the testbench can return to idle before the next case.
    R(QEN_CTRL_OFFSET) = 0u;
    wait_cycles(5000);

    printf("QB,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n",
           n,
           sw_cycles,
           sw_cycles / n,
           hw_cfg_cycles,
           useful_iters,
           (uint32_t)sw_final_pos,
           (uint32_t)hw_final_pos,
           sw_final_err,
           hw_final_err);

    if (sw_final_pos != (int32_t)n) {
        return fail_base + 1u;
    }

    if (sw_final_err != 0u) {
        return fail_base + 2u;
    }

    if (!reached) {
        return fail_base + 3u;
    }

    if (hw_final_pos != (int32_t)n) {
        return fail_base + 4u;
    }

    if (hw_final_err != 0u) {
        return fail_base + 5u;
    }

    return 0u;
}

int main(void) {
    uart_init();

    if (R(AMCP_ID_OFFSET) != 0x414D4350u) {
        return 1u;
    }

    printf("QB,N,SW,SWP,HCFG,WORK,SWPOS,HWPOS,SWERR,HWERR\n");

    uint32_t fail;

    fail = run_case(100u,  MODE_BENCH_100,  0x10u);
    if (fail) {
        uart_write_flush();
        return fail;
    }

    fail = run_case(400u,  MODE_BENCH_400,  0x20u);
    if (fail) {
        uart_write_flush();
        return fail;
    }

    fail = run_case(1600u, MODE_BENCH_1600, 0x30u);
    if (fail) {
        uart_write_flush();
        return fail;
    }

    uart_write_flush();
    return 0u;
}
