// Copyright 2022 ETH Zurich and University of Bologna.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0
//
// Nils Wistoff <nwistoff@iis.ee.ethz.ch>
// Paul Scheffler <paulsc@iis.ee.ethz.ch>

#pragma once

// Address map
#define DEBUG_BASE_ADDR     0x00000000
#define BOOTROM_BASE_ADDR   0x02000000
#define CLINT_BASE_ADDR     0x02040000
#define SOCCTRL_BASE_ADDR   0x03000000
#define UART_BASE_ADDR      0x03002000
#define GPIO_BASE_ADDR      0x03005000
#define OBI_TIMER_BASE_ADDR 0x0300A000
#define IDMA_BASE_ADDR      0x0300B000
#define USER_ROM_BASE_ADDR  0x20000000

#define AMCP_BASE_ADDR      0x20001000

#define AMCP_ID_OFFSET             0x000
#define AMCP_VERSION_OFFSET        0x004
#define AMCP_PINMUX_OFFSET         0x008
#define AMCP_STATUS_OFFSET         0x00C

#define PWM_CTRL_OFFSET            0x010
#define PWM_PERIOD_OFFSET          0x014
#define PWM_DUTY_OFFSET            0x018
#define PWM_COUNTER_OFFSET         0x01C
#define PWM_STATUS_OFFSET          0x020
#define PWM_DUTY_ACTIVE_OFFSET     0x024
#define PWM_PERIOD_ACTIVE_OFFSET   0x028

#define QEN_CTRL_OFFSET             0x040
#define QEN_STATUS_OFFSET           0x044
#define QEN_POSITION_OFFSET         0x048
#define QEN_VELOCITY_OFFSET         0x04C
#define QEN_DELTA_OFFSET            0x050
#define QEN_INDEX_POSITION_OFFSET   0x054
#define QEN_ERROR_COUNT_OFFSET      0x058
#define QEN_SAMPLE_PERIOD_OFFSET    0x05C
#define QEN_SIM_INPUT_OFFSET        0x060
#define QEN_DEBUG_OFFSET            0x064

// Frequencies
#define TB_FREQUENCY        20000000
#define TB_BAUDRATE         115200

// Peripheral configs
// UART
#define UART_BYTE_ALIGN     4
#define UART_FREQ           TB_FREQUENCY
#define UART_BAUD           TB_BAUDRATE

// Interrupts
#define IRQ_SOFTWARE        3
#define IRQ_TIMER           7
#define IRQ_EXTERNAL        11
#define IRQ_OBI_TIMER       16
#define IRQ_UART            17
#define IRQ_GPIO            18
#define IRQ_IDMA            19
