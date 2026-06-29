// Basic SRAM/data-memory test.
// Uses a large static buffer in .bss and verifies load/store correctness.
// This also checks that the enlarged SRAM/linker configuration can support
// non-trivial data memory usage.

#include <stdint.h>

#include "uart.h"
#include "print.h"
#include "util.h"
#include "config.h"

#define SRAM_WORDS 640u   // 640 * 4 = 2560 bytes, larger than a tiny smoke-test buffer

static volatile uint32_t sram_buf[SRAM_WORDS];

static uint32_t pattern_a(uint32_t i) {
    return 0xA5A50000u ^ (i * 0x01010101u) ^ ((uint32_t)(uintptr_t)&sram_buf[i] >> 2);
}

static uint32_t pattern_b(uint32_t i) {
    return 0x5A5A0000u ^ (i * 0x00110011u) ^ (i << 16) ^ (i >> 1);
}

int main(void) {
    uart_init();

    printf("SRAM test start\n");
    printf("SRAM words: 0x%x\n", SRAM_WORDS);
    printf("SRAM bytes: 0x%x\n", SRAM_WORDS * 4u);
    printf("SRAM buf base: 0x%x\n", (uint32_t)(uintptr_t)&sram_buf[0]);
    printf("SRAM buf end: 0x%x\n", (uint32_t)(uintptr_t)&sram_buf[SRAM_WORDS - 1]);

    // Pass 1: address-dependent pattern
    for (uint32_t i = 0; i < SRAM_WORDS; i++) {
        sram_buf[i] = pattern_a(i);
    }

    for (uint32_t i = 0; i < SRAM_WORDS; i++) {
        uint32_t exp = pattern_a(i);
        uint32_t got = sram_buf[i];

        if (got != exp) {
            printf("SRAM pass1 fail idx=0x%x exp=0x%x got=0x%x\n", i, exp, got);
            uart_write_flush();
            return 1;
        }
    }

    // Pass 2: inverted / second pattern
    for (uint32_t i = 0; i < SRAM_WORDS; i++) {
        sram_buf[i] = pattern_b(i);
    }

    for (uint32_t i = 0; i < SRAM_WORDS; i++) {
        uint32_t exp = pattern_b(i);
        uint32_t got = sram_buf[i];

        if (got != exp) {
            printf("SRAM pass2 fail idx=0x%x exp=0x%x got=0x%x\n", i, exp, got);
            uart_write_flush();
            return 1;
        }
    }

    // Pass 3: sparse walking-bit style check across the buffer
    for (uint32_t bit = 0; bit < 32; bit++) {
        uint32_t idx = (bit * 17u) % SRAM_WORDS;
        uint32_t val = (1u << bit) ^ 0x13572468u;

        sram_buf[idx] = val;

        if (sram_buf[idx] != val) {
            printf("SRAM walk fail bit=0x%x idx=0x%x exp=0x%x got=0x%x\n",
                   bit, idx, val, sram_buf[idx]);
            uart_write_flush();
            return 1;
        }
    }

    printf("SRAM test passed\n");
    uart_write_flush();
    return 0;
}
