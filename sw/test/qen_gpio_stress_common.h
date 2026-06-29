// Shared external-GPIO QEN stress test logic.
// Included by:
//   test_qen_gpio.c          -> silent return-code-only version
//   test_qen_gpio_verbose.c  -> UART table/report version

#include <stdint.h>

#include "util.h"
#include "config.h"

#ifdef QEN_GPIO_VERBOSE
#include "uart.h"
#include "print.h"
#endif

#ifndef QEN_CTRL_OFFSET
#define QEN_CTRL_OFFSET             0x040u
#define QEN_STATUS_OFFSET           0x044u
#define QEN_POSITION_OFFSET         0x048u
#define QEN_INDEX_POSITION_OFFSET   0x054u
#define QEN_ERROR_COUNT_OFFSET      0x058u
#define QEN_SAMPLE_PERIOD_OFFSET    0x05cu
#endif

#define QEN_EN        (1u << 0)
#define QEN_CLR_POS   (1u << 1)
#define QEN_CLR_ERR   (1u << 2)
#define QEN_IDX_RESET (1u << 3)

#define ST_IDX        (1u << 2)
#define ST_ERR        (1u << 3)

#define MODE_FWD      0x515E0001u
#define MODE_REV      0x515E0002u
#define MODE_MIX      0x515E0003u
#define MODE_INV      0x515E0004u
#define MODE_IDX      0x515E0005u
#define MODE_IDX_RST  0x515E0006u

#define R(off)        (*reg32(AMCP_BASE_ADDR, (off)))

static uint32_t fail;

static void wait_cycles(uint32_t n) {
    for (volatile uint32_t i = 0; i < n; i++) {
        asm volatile ("nop");
    }
}

static void record_fail(uint32_t code) {
    if (fail == 0u) {
        fail = code;
    }
}

static uint32_t expected_reached(
    int32_t exp_pos,
    uint32_t exp_err,
    int32_t exp_index,
    uint32_t check_index
) {
    int32_t pos = (int32_t)R(QEN_POSITION_OFFSET);
    uint32_t err = R(QEN_ERROR_COUNT_OFFSET);
    int32_t idx = (int32_t)R(QEN_INDEX_POSITION_OFFSET);
    uint32_t st = R(QEN_STATUS_OFFSET);

    if (pos != exp_pos) {
        return 0u;
    }

    if (err != exp_err) {
        return 0u;
    }

    if (check_index) {
        if (idx != exp_index) {
            return 0u;
        }

        if ((st & ST_IDX) == 0u) {
            return 0u;
        }
    }

    if (exp_err != 0u && ((st & ST_ERR) == 0u)) {
        return 0u;
    }

    return 1u;
}

static void wait_until_expected(
    int32_t exp_pos,
    uint32_t exp_err,
    int32_t exp_index,
    uint32_t check_index,
    uint32_t base_fail
) {
    // Poll instead of waiting a huge fixed delay.
    // This makes the 100 MHz silent stress run much faster.
    for (uint32_t i = 0; i < 200000u; i++) {
        if (expected_reached(exp_pos, exp_err, exp_index, check_index)) {
            return;
        }
    }

    record_fail(base_fail);
}

static void run_mode(
    uint32_t mode,
    uint32_t ctrl_extra,
    int32_t exp_pos,
    uint32_t exp_err,
    int32_t exp_index,
    uint32_t check_index,
    uint32_t base_fail
) {
    R(QEN_SAMPLE_PERIOD_OFFSET) = mode;

    // External GPIO mode:
    // QEN_SIM_INPUT_ENABLE is intentionally 0.
    R(QEN_CTRL_OFFSET) = QEN_EN | ctrl_extra | QEN_CLR_POS | QEN_CLR_ERR;
    wait_cycles(64);

    R(QEN_CTRL_OFFSET) = QEN_EN | ctrl_extra;

    wait_until_expected(
        exp_pos,
        exp_err,
        exp_index,
        check_index,
        base_fail
    );

    int32_t pos = (int32_t)R(QEN_POSITION_OFFSET);
    uint32_t err = R(QEN_ERROR_COUNT_OFFSET);
    int32_t idx = (int32_t)R(QEN_INDEX_POSITION_OFFSET);
    uint32_t st = R(QEN_STATUS_OFFSET);

#ifdef QEN_GPIO_VERBOSE
    printf("QG,0x%x,0x%x,0x%x,0x%x,0x%x\n",
           mode, (uint32_t)pos, err, (uint32_t)idx, st);
#endif

    if (pos != exp_pos) {
        record_fail(base_fail + 1u);
    }

    if (err != exp_err) {
        record_fail(base_fail + 2u);
    }

    if (check_index && idx != exp_index) {
        record_fail(base_fail + 3u);
    }

    if (check_index && ((st & ST_IDX) == 0u)) {
        record_fail(base_fail + 4u);
    }

    if ((exp_err != 0u) && ((st & ST_ERR) == 0u)) {
        record_fail(base_fail + 5u);
    }

    if ((exp_err == 0u) && ((st & ST_ERR) != 0u)) {
        record_fail(base_fail + 6u);
    }

    // Disable QEN so the testbench external stimulus loop can return idle.
    R(QEN_CTRL_OFFSET) = 0u;

    // Let the testbench finish its final hold and return to its wait state.
    wait_cycles(5000);
}

int main(void) {
#ifdef QEN_GPIO_VERBOSE
    uart_init();
#endif

    fail = 0u;

    if (R(AMCP_ID_OFFSET) != 0x414D4350u) {
        return 0x01u;
    }

#ifdef QEN_GPIO_VERBOSE
    printf("QG,mode,exp_pos,act_pos,exp_err,act_err,exp_idx,act_idx,st\n");
#endif

    run_mode(MODE_FWD,     0u,            400,  0u,   0, 0u, 0x10u);
    run_mode(MODE_REV,     0u,           -160,  0u,   0, 0u, 0x20u);
    run_mode(MODE_MIX,     0u,             80,  0u,   0, 0u, 0x30u);
    run_mode(MODE_INV,     0u,              0, 16u,   0, 0u, 0x40u);
    run_mode(MODE_IDX,     0u,             60,  0u,  40, 1u, 0x50u);
    run_mode(MODE_IDX_RST, QEN_IDX_RESET,  20,  0u,  40, 1u, 0x60u);

#ifdef QEN_GPIO_VERBOSE
    uart_write_flush();
#endif

    return fail;
}
