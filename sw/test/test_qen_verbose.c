// Verbose AMCP/QEN MMIO report test.
// Uses QEN_SIM_INPUT. Prints expected-vs-observed register values.

#include <stdint.h>

#include "uart.h"
#include "print.h"
#include "util.h"
#include "config.h"

#ifndef QEN_CTRL_OFFSET
#define QEN_CTRL_OFFSET             0x040u
#define QEN_STATUS_OFFSET           0x044u
#define QEN_POSITION_OFFSET         0x048u
#define QEN_INDEX_POSITION_OFFSET   0x054u
#define QEN_ERROR_COUNT_OFFSET      0x058u
#define QEN_SAMPLE_PERIOD_OFFSET    0x05cu
#define QEN_SIM_INPUT_OFFSET        0x060u
#define QEN_DEBUG_OFFSET            0x064u
#endif

#define QEN_EN        (1u << 0)
#define QEN_CLR_POS   (1u << 1)
#define QEN_CLR_ERR   (1u << 2)
#define QEN_IDX_RESET (1u << 3)
#define QEN_SIM       (1u << 4)

#define ST_DIR        (1u << 1)
#define ST_IDX        (1u << 2)
#define ST_ERR        (1u << 3)

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

static void check(uint32_t code, uint32_t cond) {
    if (!cond) {
        record_fail(code);
    }
}

static void qen_reset(uint32_t ctrl_extra) {
    R(QEN_SIM_INPUT_OFFSET) = 0u;
    R(QEN_SAMPLE_PERIOD_OFFSET) = 1000000u;

    R(QEN_CTRL_OFFSET) = QEN_EN | QEN_SIM | ctrl_extra | QEN_CLR_POS | QEN_CLR_ERR;
    wait_cycles(32);

    R(QEN_CTRL_OFFSET) = QEN_EN | QEN_SIM | ctrl_extra;
    wait_cycles(32);

    R(QEN_SIM_INPUT_OFFSET) = 0u;
    wait_cycles(32);
}

static void set_abz(uint32_t ab, uint32_t z) {
    uint32_t a = ab & 1u;
    uint32_t b = (ab >> 1) & 1u;

    R(QEN_SIM_INPUT_OFFSET) = a | (b << 1) | ((z & 1u) << 2);
    wait_cycles(16);
}

static void set_ab(uint32_t ab) {
    set_abz(ab, 0u);
}

static void pulse_z_at_ab(uint32_t ab) {
    set_abz(ab, 1u);
    set_abz(ab, 0u);
}

static void forward_transitions(uint32_t n) {
    static const uint32_t seq[4] = {1u, 3u, 2u, 0u};

    for (uint32_t i = 0; i < n; i++) {
        set_ab(seq[i & 3u]);
    }
}

static void reverse_transitions(uint32_t n) {
    static const uint32_t seq[4] = {2u, 3u, 1u, 0u};

    for (uint32_t i = 0; i < n; i++) {
        set_ab(seq[i & 3u]);
    }
}

static void print_row(
    uint32_t cid,
    int32_t exp_pos,
    uint32_t exp_err,
    int32_t exp_idx,
    uint32_t check_idx
) {
    int32_t pos = (int32_t)R(QEN_POSITION_OFFSET);
    uint32_t err = R(QEN_ERROR_COUNT_OFFSET);
    int32_t idx = (int32_t)R(QEN_INDEX_POSITION_OFFSET);
    uint32_t st = R(QEN_STATUS_OFFSET);

    printf("QM,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x\n",
           cid,
           (uint32_t)exp_pos,
           (uint32_t)pos,
           exp_err,
           err,
           (uint32_t)exp_idx,
           (uint32_t)idx,
           st);

    check(cid + 1u, pos == exp_pos);
    check(cid + 2u, err == exp_err);

    if (check_idx) {
        check(cid + 3u, idx == exp_idx);
        check(cid + 4u, (st & ST_IDX) != 0u);
    }

    if (exp_err != 0u) {
        check(cid + 5u, (st & ST_ERR) != 0u);
    }
}

int main(void) {
    uart_init();
    fail = 0u;

    if (R(AMCP_ID_OFFSET) != 0x414D4350u) {
        return 0x01u;
    }

    printf("QM,case,exp_pos,act_pos,exp_err,act_err,exp_idx,act_idx,status\n");

    // Case 0x10: forward +4.
    qen_reset(0u);
    forward_transitions(4u);
    print_row(0x10u, 4, 0u, 0, 0u);
    check(0x16u, (R(QEN_STATUS_OFFSET) & ST_DIR) != 0u);

    // Case 0x20: reverse -4.
    qen_reset(0u);
    reverse_transitions(4u);
    print_row(0x20u, -4, 0u, 0, 0u);
    check(0x26u, (R(QEN_STATUS_OFFSET) & ST_DIR) == 0u);

    // Case 0x30: mixed +8 then -3 = +5.
    qen_reset(0u);
    forward_transitions(8u);
    reverse_transitions(3u);
    print_row(0x30u, 5, 0u, 0, 0u);

    // Case 0x40: two invalid transitions 00->11 and 11->00.
    qen_reset(0u);
    set_ab(3u);
    set_ab(0u);
    print_row(0x40u, 0, 2u, 0, 0u);

    // Case 0x50: clear error after invalid transitions.
    R(QEN_CTRL_OFFSET) = QEN_EN | QEN_SIM | QEN_CLR_ERR;
    wait_cycles(32);
    R(QEN_CTRL_OFFSET) = QEN_EN | QEN_SIM;
    wait_cycles(32);
    print_row(0x50u, 0, 0u, 0, 0u);

    // Case 0x60: clear position after motion.
    forward_transitions(4u);
    R(QEN_CTRL_OFFSET) = QEN_EN | QEN_SIM | QEN_CLR_POS;
    wait_cycles(32);
    R(QEN_CTRL_OFFSET) = QEN_EN | QEN_SIM;
    wait_cycles(32);
    print_row(0x60u, 0, 0u, 0, 0u);

    // Case 0x70: index capture without reset.
    qen_reset(0u);
    forward_transitions(8u);
    pulse_z_at_ab(0u);
    forward_transitions(4u);
    print_row(0x70u, 12, 0u, 8, 1u);

    // Case 0x80: index capture with reset.
    qen_reset(QEN_IDX_RESET);
    forward_transitions(8u);
    pulse_z_at_ab(0u);
    forward_transitions(4u);
    print_row(0x80u, 4, 0u, 8, 1u);

    // Case 0x90: debug register low bits.
    qen_reset(0u);
    set_abz(1u, 1u);
    uint32_t dbg = R(QEN_DEBUG_OFFSET) & 0x1fu;
    printf("QD,0x15,0x%x\n", dbg);
    check(0x90u, dbg == 0x15u);

    uart_write_flush();
    return fail;
}
