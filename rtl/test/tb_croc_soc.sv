
// uncomment the first block to run power analysis.

// Copyright 2024 ETH Zurich and University of Bologna.
// Solderpad Hardware License, Version 0.51, see LICENSE for details.
// SPDX-License-Identifier: SHL-0.51
//
// Authors:
// - Philippe Sauter <phsauter@iis.ee.ethz.ch>
// - Enrico Zelioli <ezelioli@iis.ee.ethz.ch>

`define TRACE_WAVE

module tb_croc_soc #(
  parameter int unsigned GpioCount = 32
);

  import tb_croc_pkg::*;

  // Signals fully controlled by the VIP
  // use VIP functions/tasks to manipulate these signals
  logic rst_n;
  logic sys_clk;
  logic ref_clk;

  logic jtag_tck;
  logic jtag_trst_n;
  logic jtag_tms;
  logic jtag_tdi;
  logic jtag_tdo;

  logic uart_rx;
  logic uart_tx;

  // Signals partially controlled by the VIP
  logic [GpioCount-1:0] gpio_in;
  logic [GpioCount-1:0] gpio_out;
  logic [GpioCount-1:0] gpio_out_en;

  // Optional external GPIO stimulus driven directly by this testbench.
  logic [GpioCount-1:0] gpio_in_ext;
  logic [GpioCount-1:0] gpio_in_ext_oe;

  // Signals controlled by the testbench

  /////////////////////////////
  //  Command Line Arguments //
  /////////////////////////////

  string binary_path;

  initial begin
    // $value$plusargs defines what to look for (here +binary=...)
    if ($value$plusargs("binary=%s", binary_path)) begin
      $display("Running program: %s", binary_path);
    end else begin
      $display("No binary path provided. Running helloworld.");
      binary_path = "../sw/bin/helloworld.hex";
    end
  end

  ////////////
  //  VIP   //
  ////////////
  // Verification IP
  // - drives clocks and resets
  // - provides helper tasks and functions for JTAG, namely:
  //   - jtag_load_hex: loads a hex file into the DUT's memory
  //   - jtag_write_reg32: write 32-bit value to DUT
  //   - jtag_read_reg32: read 32-bit value from DUT
  //   - jtag_halt / jtag_resume: control core execution
  //   - jtag_wait_for_eoc: wait for end of code execution (core writes non-zero to status register)
  // - prints UART output to console (you can also write via uart_write_byte)
  // - internal GPIO loopback for helloworld test

  croc_vip #(
    .GpioCount ( GpioCount )
  ) i_vip (
    .rst_no        ( rst_n       ),
    .sys_clk_o     ( sys_clk     ),
    .ref_clk_o     ( ref_clk     ),
    .jtag_tck_o    ( jtag_tck    ),
    .jtag_trst_no  ( jtag_trst_n ),
    .jtag_tms_o    ( jtag_tms    ),
    .jtag_tdi_o    ( jtag_tdi    ),
    .jtag_tdo_i    ( jtag_tdo    ),
    .uart_rx_o     ( uart_rx     ),
    .uart_tx_i     ( uart_tx     ),
    .gpio_out_en_i     ( gpio_out_en     ),
    .gpio_out_i        ( gpio_out        ),
    .gpio_in_ext_i     ( gpio_in_ext     ),
    .gpio_in_ext_oe_i  ( gpio_in_ext_oe  ),
    .gpio_in_o         ( gpio_in         )
  );

  ////////////
  //  DUT   //
  ////////////

  `ifdef TARGET_NETLIST_OPENROAD
    wire [GpioCount-1:0] gpio_io_tb;

    // For pad-level simulation:
    // - external/testbench-driven GPIOs are driven through gpio_in_ext_oe
    // - otherwise the pad is left high-Z so DUT outputs can drive it
    for (genvar i = 0; i < GpioCount; i++) begin : gen_gpio_pad_drive
      assign gpio_io_tb[i] = gpio_in_ext_oe[i] ? gpio_in_ext[i] : 1'bz;
    end

    assign gpio_out = gpio_io_tb;
    assign gpio_out_en = '0;
    croc_chip i_croc_soc (
      .clk_i         ( sys_clk        ),
      .rst_ni        ( rst_n          ),
      .ref_clk_i     ( ref_clk        ),
      .testmode_i    ( 1'b0           ),
      .status_o      (                ),
      .jtag_tck_i    ( jtag_tck       ),
      .jtag_tdi_i    ( jtag_tdi       ),
      .jtag_tdo_o    ( jtag_tdo       ),
      .jtag_tms_i    ( jtag_tms       ),
      .jtag_trst_ni  ( jtag_trst_n    ),
      .uart_rx_i     ( uart_rx        ),
      .uart_tx_o     ( uart_tx        ),

      .gpio0_io      ( gpio_io_tb[0]  ),
      .gpio1_io      ( gpio_io_tb[1]  ),
      .gpio2_io      ( gpio_io_tb[2]  ),
      .gpio3_io      ( gpio_io_tb[3]  ),
      .gpio4_io      ( gpio_io_tb[4]  ),
      .gpio5_io      ( gpio_io_tb[5]  ),
      .gpio6_io      ( gpio_io_tb[6]  ),
      .gpio7_io      ( gpio_io_tb[7]  ),
      .gpio8_io      ( gpio_io_tb[8]  ),
      .gpio9_io      ( gpio_io_tb[9]  ),
      .gpio10_io     ( gpio_io_tb[10] ),
      .gpio11_io     ( gpio_io_tb[11] ),
      .gpio12_io     ( gpio_io_tb[12] ),
      .gpio13_io     ( gpio_io_tb[13] ),
      .gpio14_io     ( gpio_io_tb[14] ),
      .gpio15_io     ( gpio_io_tb[15] ),
      .gpio16_io     ( gpio_io_tb[16] ),
      .gpio17_io     ( gpio_io_tb[17] ),
      .gpio18_io     ( gpio_io_tb[18] ),
      .gpio19_io     ( gpio_io_tb[19] ),
      .gpio20_io     ( gpio_io_tb[20] ),
      .gpio21_io     ( gpio_io_tb[21] ),
      .gpio22_io     ( gpio_io_tb[22] ),
      .gpio23_io     ( gpio_io_tb[23] ),
      .gpio24_io     ( gpio_io_tb[24] ),
      .gpio25_io     ( gpio_io_tb[25] ),
      .gpio26_io     ( gpio_io_tb[26] ),
      .gpio27_io     ( gpio_io_tb[27] ),
      .gpio28_io     ( gpio_io_tb[28] ),
      .gpio29_io     ( gpio_io_tb[29] ),
      .gpio30_io     ( gpio_io_tb[30] ),
      .gpio31_io     ( gpio_io_tb[31] ),

      .unused0_o     (                ),
      .unused1_o     (                ),
      .unused2_o     (                ),
      .unused3_o     (                )
    );
  `else
    `ifdef TARGET_NETLIST_YOSYS
    \croc_soc$croc_chip.i_croc_soc i_croc_soc (
    `else
    croc_soc #(
      .GpioCount ( GpioCount )
    ) i_croc_soc (
    `endif
    .clk_i         ( sys_clk     ),
    .rst_ni        ( rst_n       ),
    .ref_clk_i     ( ref_clk     ),
    .testmode_i    ( 1'b0        ),
    .status_o      (             ),
    .jtag_tck_i    ( jtag_tck    ),
    .jtag_tdi_i    ( jtag_tdi    ),
    .jtag_tdo_o    ( jtag_tdo    ),
    .jtag_tms_i    ( jtag_tms    ),
    .jtag_trst_ni  ( jtag_trst_n ),
    .uart_rx_i     ( uart_rx     ),
    .uart_tx_o     ( uart_tx     ),
    .gpio_i        ( gpio_in     ),
    .gpio_o        ( gpio_out    ),
    .gpio_out_en_o ( gpio_out_en )
  );
  `endif
  // Debug aliases for waveform inspection.
  // These make GTKWave much easier than manually decoding gpio_out[31:0].
  logic dbg_gpio0_pwm;
  logic dbg_gpio0_out_en;
  logic dbg_amcp_pwm_o;
  logic [15:0] dbg_pwm_counter;
  logic [15:0] dbg_pwm_period_active;
  logic [15:0] dbg_pwm_duty_active;

  // QEN debug aliases for GTKWave.
  logic dbg_qen_a;
  logic dbg_qen_b;
  logic dbg_qen_z;
  logic dbg_qen_enable;
  logic dbg_qen_sim_input_enable;
  logic dbg_qen_index_reset_enable;
  logic dbg_qen_direction;
  logic dbg_qen_index_seen;
  logic dbg_qen_invalid_transition;
  logic dbg_qen_velocity_valid;
  logic [1:0] dbg_qen_ab_state;
  logic [2:0] dbg_qen_sim_input;
  logic [31:0] dbg_qen_error_count;
  logic signed [31:0] dbg_qen_position;
  logic signed [31:0] dbg_qen_velocity;
  logic signed [31:0] dbg_qen_delta;
  logic signed [31:0] dbg_qen_index_position;
  logic dbg_qen_ext_stim_active;

    // Debug aliases for GTKWave inspection in comparison between software and hardware.
  logic dbg_gpio1_sw_marker;
  logic dbg_gpio2_hw_marker;
  assign dbg_gpio1_sw_marker = gpio_out[1];
  assign dbg_gpio2_hw_marker = gpio_out[2];

  assign dbg_gpio0_pwm         = gpio_out[0];
  assign dbg_gpio0_out_en      = gpio_out_en[0];
  `ifndef TARGET_NETLIST_OPENROAD
    assign dbg_amcp_pwm_o        = i_croc_soc.i_user.i_user_amcp.pwm_o;
    assign dbg_pwm_counter       = i_croc_soc.i_user.i_user_amcp.i_pwm_core.counter_o;
    assign dbg_pwm_period_active = i_croc_soc.i_user.i_user_amcp.i_pwm_core.period_active_o;
    assign dbg_pwm_duty_active   = i_croc_soc.i_user.i_user_amcp.i_pwm_core.duty_active_o;

    assign dbg_qen_a                  = i_croc_soc.i_user.i_user_amcp.qen_a;
    assign dbg_qen_b                  = i_croc_soc.i_user.i_user_amcp.qen_b;
    assign dbg_qen_z                  = i_croc_soc.i_user.i_user_amcp.qen_z;
    assign dbg_qen_enable             = i_croc_soc.i_user.i_user_amcp.qen_enable_q;
    assign dbg_qen_sim_input_enable   = i_croc_soc.i_user.i_user_amcp.qen_sim_input_enable_q;
    assign dbg_qen_index_reset_enable = i_croc_soc.i_user.i_user_amcp.qen_index_reset_enable_q;
    assign dbg_qen_sim_input          = i_croc_soc.i_user.i_user_amcp.qen_sim_input_q;
    assign dbg_qen_position           = i_croc_soc.i_user.i_user_amcp.qen_position;
    assign dbg_qen_velocity           = i_croc_soc.i_user.i_user_amcp.qen_velocity;
    assign dbg_qen_delta              = i_croc_soc.i_user.i_user_amcp.qen_delta;
    assign dbg_qen_index_position     = i_croc_soc.i_user.i_user_amcp.qen_index_position;
    assign dbg_qen_error_count        = i_croc_soc.i_user.i_user_amcp.qen_error_count;
    assign dbg_qen_direction          = i_croc_soc.i_user.i_user_amcp.qen_direction;
    assign dbg_qen_index_seen         = i_croc_soc.i_user.i_user_amcp.qen_index_seen;
    assign dbg_qen_invalid_transition = i_croc_soc.i_user.i_user_amcp.qen_invalid_transition;
    assign dbg_qen_velocity_valid     = i_croc_soc.i_user.i_user_amcp.qen_velocity_valid;
    assign dbg_qen_ab_state           = i_croc_soc.i_user.i_user_amcp.qen_ab_state;
  `else
    assign dbg_amcp_pwm_o             = gpio_out[0];
    assign dbg_pwm_counter            = '0;
    assign dbg_pwm_period_active      = '0;
    assign dbg_pwm_duty_active        = '0;

    assign dbg_qen_a                  = gpio_in_ext[1];
    assign dbg_qen_b                  = gpio_in_ext[2];
    assign dbg_qen_z                  = gpio_in_ext[3];
    assign dbg_qen_enable             = '0;
    assign dbg_qen_sim_input_enable   = '0;
    assign dbg_qen_index_reset_enable = '0;
    assign dbg_qen_sim_input          = '0;
    assign dbg_qen_position           = '0;
    assign dbg_qen_velocity           = '0;
    assign dbg_qen_delta              = '0;
    assign dbg_qen_index_position     = '0;
    assign dbg_qen_error_count        = '0;
    assign dbg_qen_direction          = '0;
    assign dbg_qen_index_seen         = '0;
    assign dbg_qen_invalid_transition = '0;
    assign dbg_qen_velocity_valid     = '0;
    assign dbg_qen_ab_state           = '0;
  `endif  

  localparam int unsigned QenGpioA = 1;
  localparam int unsigned QenGpioB = 2;
  localparam int unsigned QenGpioZ = 3;
  localparam int unsigned QenStimHoldCycles = 4;

  // QEN external-stimulus mode selector.
  // Firmware writes one of these values into QEN_SAMPLE_PERIOD_OFFSET.
  localparam logic [31:0] QenModeForwardStress = 32'h515E_0001;
  localparam logic [31:0] QenModeReverseStress = 32'h515E_0002;
  localparam logic [31:0] QenModeMixedDir      = 32'h515E_0003;
  localparam logic [31:0] QenModeInvalidBurst  = 32'h515E_0004;
  localparam logic [31:0] QenModeIndexNoReset  = 32'h515E_0005;
  localparam logic [31:0] QenModeIndexReset    = 32'h515E_0006;

  // QEN scaling benchmark modes. Lower 16 bits encode N in hex.
  localparam logic [31:0] QenBench100  = 32'h515E_0064;
  localparam logic [31:0] QenBench400  = 32'h515E_0190;
  localparam logic [31:0] QenBench1600 = 32'h515E_0640;
  localparam logic [31:0] QenModeMotorPlant = 32'h515E_C10D;


  `ifndef TARGET_NETLIST_OPENROAD

    // --------------------------------------------------------------------------
    // Buck-converter closed-loop plant and PWM-resolution monitor
    // --------------------------------------------------------------------------
    // Testbench-only model.
    //
    // GPIO0      = real AMCP PWM output
    // GPIO5      = firmware marker: closed-loop buck PID active
    // GPIO6      = firmware marker: PWM-resolution sweep active
    // GPIO[8:17] = fake 10-bit ADC feedback driven by this testbench
    //
    // This models the missing ADC path for a buck converter:
    //   PWM -> buck plant -> ADC code -> firmware PID -> PWM_DUTY

    localparam int unsigned BuckPwmPeriodCycles = 100;  // 100 MHz / 100 = 1 MHz
    localparam int signed   BuckVinMv           = 1200;
    localparam int signed   BuckTargetMv        = 700;
    localparam int unsigned BuckTauShift        = 3;    // response factor 1/8 per PWM period
    localparam int unsigned BuckAdcBase         = 8;
    localparam int unsigned BuckAdcBits         = 10;
    localparam int unsigned BuckPidMarker       = 5;
    localparam int unsigned BuckResMarker       = 6;
    localparam int unsigned BuckPrintEvery      = 256;

    int unsigned buck_period_idx;
    int unsigned buck_high_count;
    int unsigned buck_duty_x1000;
    int unsigned buck_adc_code;
    int signed   buck_target_mv;
    int signed   buck_vout_mv;
    int signed   buck_err_mv;
    int signed   buck_step_mv;

    bit buck_seen_high_count [0:BuckPwmPeriodCycles];
    int unsigned buck_seen_levels;
    int unsigned buck_min_high_seen;
    int unsigned buck_max_high_seen;

    task automatic buck_drive_adc(input int signed vout_mv);
      int signed vclip;
      int unsigned code;
      begin
        vclip = vout_mv;

        if (vclip < 0) begin
          vclip = 0;
        end

        if (vclip > BuckVinMv) begin
          vclip = BuckVinMv;
        end

        code = (int'(vclip) * 1023 + (BuckVinMv / 2)) / BuckVinMv;
        buck_adc_code = code;

        for (int unsigned i = 0; i < BuckAdcBits; i++) begin
          gpio_in_ext_oe[BuckAdcBase + i] = 1'b1;
          gpio_in_ext[BuckAdcBase + i]    = code[i];
        end
      end
    endtask

    task automatic buck_measure_one_pwm_period;
      begin
        buck_high_count = 0;

        for (int unsigned i = 0; i < BuckPwmPeriodCycles; i++) begin
          @(posedge sys_clk);

          if (gpio_out[0]) begin
            buck_high_count++;
          end
        end
      end
    endtask

    task automatic buck_update_plant_from_pwm;
      begin
        buck_measure_one_pwm_period();

        buck_duty_x1000 = (1000 * buck_high_count) / BuckPwmPeriodCycles;
        buck_target_mv  = (BuckVinMv * int'(buck_high_count)) / int'(BuckPwmPeriodCycles);

        buck_err_mv = buck_target_mv - buck_vout_mv;

        // Signed rounded divide by 8.
        if (buck_err_mv >= 0) begin
          buck_step_mv = (buck_err_mv + (1 << (BuckTauShift - 1))) >>> BuckTauShift;
        end else begin
          buck_step_mv = -(((-buck_err_mv) + (1 << (BuckTauShift - 1))) >>> BuckTauShift);
        end

        buck_vout_mv += buck_step_mv;
        buck_drive_adc(buck_vout_mv);

        buck_period_idx++;
      end
    endtask

    initial begin
      buck_period_idx = 0;
      buck_high_count = 0;
      buck_duty_x1000 = 0;
      buck_adc_code   = 0;
      buck_target_mv  = 0;
      buck_vout_mv    = 0;
      buck_err_mv     = 0;
      buck_step_mv    = 0;

      @(posedge rst_n);

      // Start with ADC code = 0 mV.
      buck_drive_adc(0);

      forever begin
        wait (gpio_out[BuckPidMarker] === 1'b1);

        buck_period_idx = 0;
        buck_vout_mv    = 0;
        buck_drive_adc(0);

        $display("@%t | [BUCK_PID] Closed-loop buck plant started", $time);
        $display("@%t | [BUCK_PID] Vin=%0d mV target=%0d mV PWM_period=%0d cycles resolution=1%%",
                 $time, BuckVinMv, BuckTargetMv, BuckPwmPeriodCycles);

        while (gpio_out[BuckPidMarker] === 1'b1) begin
          buck_update_plant_from_pwm();

          if ((buck_period_idx <= 16) || ((buck_period_idx % BuckPrintEvery) == 0)) begin
            $display("@%t | [BUCK_PID] n=%0d high=%0d duty_x1000=%0d target_from_pwm_mV=%0d vout_mV=%0d adc=%0d err_to_ref_mV=%0d",
                     $time,
                     buck_period_idx,
                     buck_high_count,
                     buck_duty_x1000,
                     buck_target_mv,
                     buck_vout_mv,
                     buck_adc_code,
                     BuckTargetMv - buck_vout_mv);
          end
        end

        $display("@%t | [BUCK_PID] Closed-loop buck plant stopped after %0d PWM periods, final_vout_mV=%0d final_err_mV=%0d",
                 $time,
                 buck_period_idx,
                 buck_vout_mv,
                 BuckTargetMv - buck_vout_mv);
      end
    end

    initial begin
      @(posedge rst_n);

      forever begin
        wait (gpio_out[BuckResMarker] === 1'b1);

        for (int unsigned i = 0; i <= BuckPwmPeriodCycles; i++) begin
          buck_seen_high_count[i] = 1'b0;
        end

        buck_seen_levels   = 0;
        buck_min_high_seen = BuckPwmPeriodCycles;
        buck_max_high_seen = 0;

        $display("@%t | [PWM_RES] Resolution sweep started: clk=100MHz pwm=1MHz period=%0d cycles",
                 $time, BuckPwmPeriodCycles);

        while (gpio_out[BuckResMarker] === 1'b1) begin
          buck_measure_one_pwm_period();

          if (buck_high_count <= BuckPwmPeriodCycles) begin
            if (!buck_seen_high_count[buck_high_count]) begin
              buck_seen_high_count[buck_high_count] = 1'b1;
              buck_seen_levels++;

              if (buck_high_count < buck_min_high_seen) begin
                buck_min_high_seen = buck_high_count;
              end

              if (buck_high_count > buck_max_high_seen) begin
                buck_max_high_seen = buck_high_count;
              end
            end
          end
        end

        $display("@%t | [PWM_RES] observed_levels=%0d min_high=%0d max_high=%0d expected_levels=%0d step_percent=1",
                 $time,
                 buck_seen_levels,
                 buck_min_high_seen,
                 buck_max_high_seen,
                 BuckPwmPeriodCycles + 1);

        if ((buck_seen_levels == (BuckPwmPeriodCycles + 1)) &&
            (buck_min_high_seen == 0) &&
            (buck_max_high_seen == BuckPwmPeriodCycles)) begin
          $display("@%t | [PWM_RES] PASS: 1%% duty resolution verified at 1 MHz PWM", $time);
        end else begin
          $display("@%t | [PWM_RES] WARN: full 1%% sweep not completely observed", $time);
        end
      end
    end

  `endif

  task automatic drive_qen_abz(
    input logic a,
    input logic b,
    input logic z
  );
    gpio_in_ext_oe[QenGpioA] = 1'b1;
    gpio_in_ext_oe[QenGpioB] = 1'b1;
    gpio_in_ext_oe[QenGpioZ] = 1'b1;

    gpio_in_ext[QenGpioA] = a;
    gpio_in_ext[QenGpioB] = b;
    gpio_in_ext[QenGpioZ] = z;

    repeat (QenStimHoldCycles) @(posedge sys_clk);
  endtask

  task automatic drive_qen_forward_transitions(input int unsigned n);
    for (int unsigned i = 0; i < n; i++) begin
      case (i % 4)
        0: drive_qen_abz(1'b1, 1'b0, 1'b0); // 01
        1: drive_qen_abz(1'b1, 1'b1, 1'b0); // 11
        2: drive_qen_abz(1'b0, 1'b1, 1'b0); // 10
        default: drive_qen_abz(1'b0, 1'b0, 1'b0); // 00
      endcase
    end
  endtask

  task automatic drive_qen_reverse_transitions(input int unsigned n);
    for (int unsigned i = 0; i < n; i++) begin
      case (i % 4)
        0: drive_qen_abz(1'b0, 1'b1, 1'b0); // 10
        1: drive_qen_abz(1'b1, 1'b1, 1'b0); // 11
        2: drive_qen_abz(1'b1, 1'b0, 1'b0); // 01
        default: drive_qen_abz(1'b0, 1'b0, 1'b0); // 00
      endcase
    end
  endtask



  logic [1:0] qen_plant_ab;

  task automatic qen_plant_drive_ab(input logic [1:0] ab);
    begin
      qen_plant_ab = ab;
      // drive_qen_abz arguments are a,b,z.
      drive_qen_abz(ab[0], ab[1], 1'b0);
    end
  endtask

  task automatic qen_plant_forward_one;
    begin
      case (qen_plant_ab)
        2'b00: qen_plant_drive_ab(2'b01);
        2'b01: qen_plant_drive_ab(2'b11);
        2'b11: qen_plant_drive_ab(2'b10);
        default: qen_plant_drive_ab(2'b00);
      endcase
    end
  endtask

  task automatic qen_plant_reverse_one;
    begin
      case (qen_plant_ab)
        2'b00: qen_plant_drive_ab(2'b10);
        2'b10: qen_plant_drive_ab(2'b11);
        2'b11: qen_plant_drive_ab(2'b01);
        default: qen_plant_drive_ab(2'b00);
      endcase
    end
  endtask

  task automatic qen_plant_drive_steps(input int signed steps);
    begin
      if (steps > 0) begin
        repeat (steps) begin
          qen_plant_forward_one();
        end
      end else if (steps < 0) begin
        repeat (-steps) begin
          qen_plant_reverse_one();
        end
      end
    end
  endtask
`ifndef TARGET_NETLIST_OPENROAD
  task automatic run_qen_motor_plant(input int unsigned max_windows);
    int unsigned high_count;
    int signed effort;
    int signed target_vel_q8;
    int signed vel_q8;
    int signed frac_q8;
    int signed steps;
    int unsigned w;
    begin
      $display("@%t | [QEN_PLANT] Motor plant started", $time);

      qen_plant_ab = 2'b00;
      vel_q8  = 0;
      frac_q8 = 0;
      w       = 0;

      // Start encoder at AB=00, Z=0.
      qen_plant_drive_ab(2'b00);

      while (i_croc_soc.i_user.i_user_amcp.qen_enable_q &&
             (i_croc_soc.i_user.i_user_amcp.qen_sample_period_q == QenModeMotorPlant) &&
             ((max_windows == 0) || (w < max_windows))) begin

        // Measure actual AMCP PWM output over one PWM period.
        // Firmware programs PWM_PERIOD = 100.
        high_count = 0;

        for (int unsigned i = 0; i < 100; i++) begin
          @(posedge sys_clk);

          if (i_croc_soc.i_user.i_user_amcp.pwm_o) begin
            high_count++;
          end
        end

        // Simple closed-loop plant model:
        // Measure actual PWM high_count over one PWM period.
        //
        // high_count = 50 -> zero motion
        // high_count > 50 -> positive QEN position motion
        // high_count < 50 -> negative QEN position motion
        //
        // We intentionally generate at most one encoder transition every
        // 32 PWM windows. This makes plant dynamics slower than the CPU
        // control loop and avoids violent overshoot.
        effort = int'(high_count) - 50;

        if ((w < 20) || ((w % 512) == 0)) begin
          $display("@%t | [PDBG] w=%0d high=%0d effort=%0d ab=%b",
                   $time, w, high_count, effort, qen_plant_ab);
        end

        if ((w % 64) == 0) begin
          if (effort > 6) begin
            // Positive PWM effort should increase QEN position.
            qen_plant_forward_one();
          end else if (effort < -6) begin
            // Negative PWM effort should decrease QEN position.
            qen_plant_reverse_one();
          end
        end

        w++;
      end

      $display("@%t | [QEN_PLANT] Motor plant stopped after %0d windows", $time, w);
    end
  endtask
`endif

  task automatic drive_qen_invalid_burst(input int unsigned n);
    // Starting from 00, alternate 00 <-> 11.
    // Each transition changes both A and B, so every transition is invalid.
    for (int unsigned i = 0; i < n; i++) begin
      if ((i % 2) == 0) begin
        drive_qen_abz(1'b1, 1'b1, 1'b0); // 11
      end else begin
        drive_qen_abz(1'b0, 1'b0, 1'b0); // 00
      end
    end
  endtask

  initial begin
    gpio_in_ext             = '0;
    gpio_in_ext_oe          = '0;
    dbg_qen_ext_stim_active = 1'b0;
  end

`ifndef TARGET_NETLIST_OPENROAD
  // External encoder stimulus.
  // This block stays idle for normal tests. It only runs when firmware enables
  // QEN with sim_input_enable = 0.
  initial begin
    @(posedge rst_n);

    forever begin
      wait (i_croc_soc.i_user.i_user_amcp.qen_enable_q &&
            !i_croc_soc.i_user.i_user_amcp.qen_sim_input_enable_q);

      dbg_qen_ext_stim_active = 1'b1;

      // Hold initial encoder state long enough for QEN to initialize prev_ab.
      drive_qen_abz(1'b0, 1'b0, 1'b0);
      repeat (100) @(posedge sys_clk);

      unique case (i_croc_soc.i_user.i_user_amcp.qen_sample_period_q)

        QenBench100: begin
          // Expected: benchmark position = +100, error_count = 0.
          drive_qen_forward_transitions(100);
          repeat (500) @(posedge sys_clk);
        end

        QenBench400: begin
          // Expected: benchmark position = +400, error_count = 0.
          drive_qen_forward_transitions(400);
          repeat (500) @(posedge sys_clk);
        end

        QenBench1600: begin
          // Expected: benchmark position = +1600, error_count = 0.
          drive_qen_forward_transitions(1600);
          repeat (500) @(posedge sys_clk);
        end

        QenModeMotorPlant: begin
          // Closed-loop PID demo:
          // actual hardware PWM output -> testbench motor model -> external QEN GPIO A/B.
          run_qen_motor_plant(0);
          repeat (500) @(posedge sys_clk);
        end

        QenModeForwardStress: begin
          // Expected: position = +400, error_count = 0.
          drive_qen_forward_transitions(400);
          repeat (500) @(posedge sys_clk);
        end

        QenModeReverseStress: begin
          // Expected: position = -160, error_count = 0.
          drive_qen_reverse_transitions(160);
          repeat (500) @(posedge sys_clk);
        end

        QenModeMixedDir: begin
          // Expected: +128 - 48 = +80, error_count = 0.
          drive_qen_forward_transitions(128);
          drive_qen_reverse_transitions(48);
          repeat (500) @(posedge sys_clk);
        end

        QenModeInvalidBurst: begin
          // Expected: position = 0, error_count = 16.
          drive_qen_invalid_burst(16);
          repeat (500) @(posedge sys_clk);
        end

        QenModeIndexNoReset: begin
          // Expected: move to 40, capture index_position=40,
          // then continue to final position 60.
          drive_qen_forward_transitions(40);
          drive_qen_abz(1'b0, 1'b0, 1'b1); // Z high at position 40
          drive_qen_abz(1'b0, 1'b0, 1'b0); // Z low
          drive_qen_forward_transitions(20);
          repeat (500) @(posedge sys_clk);
        end

        QenModeIndexReset: begin
          // Firmware enables index_reset.
          // Expected: move to 40, capture index_position=40,
          // reset live position to 0, then move 20 more -> final position 20.
          drive_qen_forward_transitions(40);
          drive_qen_abz(1'b0, 1'b0, 1'b1); // Z high at position 40
          drive_qen_abz(1'b0, 1'b0, 1'b0); // Z low
          drive_qen_forward_transitions(20);
          repeat (500) @(posedge sys_clk);
        end

        default: begin
          // Legacy directed demo mode:
          // forward +4, index, one invalid jump.
          drive_qen_forward_transitions(4);
          drive_qen_abz(1'b0, 1'b0, 1'b1);
          drive_qen_abz(1'b0, 1'b0, 1'b0);
          drive_qen_abz(1'b1, 1'b1, 1'b0);
          repeat (200) @(posedge sys_clk);
        end

      endcase

      dbg_qen_ext_stim_active = 1'b0;

      wait (!i_croc_soc.i_user.i_user_amcp.qen_enable_q ||
             i_croc_soc.i_user.i_user_amcp.qen_sim_input_enable_q);
    end
  end 
  `endif

  
  /////////////////
  //  Testbench  //
  /////////////////

  logic [31:0] tb_data;

  initial begin
    $timeformat(-9, 0, "ns", 12); // 1: scale (ns=-9), 2: decimals, 3: suffix, 4: print-field width

    // wait for reset
    #ClkPeriodSys;

    // init jtag
    i_vip.jtag_init();

    // write test value to sram
    i_vip.jtag_write_reg32(SramBaseAddr, 32'h1234_5678, 1'b1);

    // load binary to sram
    i_vip.jtag_load_hex(binary_path);

    // wake core from WFI by writing to CLINT msip
    $display("@%t | [CORE] Waking core via CLINT msip", $time);
    i_vip.jtag_write_reg32(ClintBaseAddr, 32'h1);

    // halt core
    i_vip.jtag_halt();

    // resume core
    i_vip.jtag_resume();

    if ($test$plusargs("power_vcd")) begin
      `ifdef TRACE_WAVE
        // For power analysis, wait until firmware enters the actual workload.
        // GPIO7 is used as a firmware marker: 1 = benchmark loop active.
        $display("@%t | [VCD] Waiting for GPIO7 power marker...", $time);
        wait (gpio_out[7] === 1'b1);

        $display("@%t | [VCD] Start active-workload dump", $time);

        $dumpfile("croc.vcd");
        $dumpvars(0, i_croc_soc);

        // 40000 cycles at 100 MHz = 400 us.
        repeat (40000) @(posedge sys_clk);

        $display("@%t | [VCD] Stop active-workload dump", $time);
        $dumpoff;
        $dumpflush;

        $finish();
      `else
        $display("@%t | [VCD] ERROR: +power_vcd requested but TRACE_WAVE is not defined", $time);
        $finish();
      `endif
    end else begin
      // Normal functional simulation path.
      // Wait for non-zero return value written into the core status register.
      $display("@%t | [CORE] Wait for end of code...", $time);
      i_vip.jtag_wait_for_eoc(tb_data);
    end

    // finish simulation
    repeat(50) @(posedge sys_clk);
    $finish();
  end

  ////////////////
  //  Waveform  //
  ////////////////
  // start waveform dump at time 0, independent of stimuli
  initial begin
    `ifdef TRACE_WAVE
      `ifdef VERILATOR
        $dumpfile("croc.fst");
        $dumpvars(1, i_croc_soc);

        // Also dump selected scalar debug aliases from the testbench.
        $dumpvars(0, dbg_gpio0_pwm);
        $dumpvars(0, dbg_gpio0_out_en);
        $dumpvars(0, dbg_amcp_pwm_o);
        $dumpvars(0, dbg_pwm_counter);
        $dumpvars(0, dbg_pwm_period_active);
        $dumpvars(0, dbg_pwm_duty_active);
        $dumpvars(0, dbg_gpio1_sw_marker);
        $dumpvars(0, dbg_gpio2_hw_marker);

        $dumpvars(0, dbg_qen_a);
        $dumpvars(0, dbg_qen_b);
        $dumpvars(0, dbg_qen_z);
        $dumpvars(0, dbg_qen_enable);
        $dumpvars(0, dbg_qen_sim_input_enable);
        $dumpvars(0, dbg_qen_index_reset_enable);
        $dumpvars(0, dbg_qen_sim_input);
        $dumpvars(0, dbg_qen_position);
        $dumpvars(0, dbg_qen_velocity);
        $dumpvars(0, dbg_qen_delta);
        $dumpvars(0, dbg_qen_index_position);
        $dumpvars(0, dbg_qen_error_count);
        $dumpvars(0, dbg_qen_direction);
        $dumpvars(0, dbg_qen_index_seen);
        $dumpvars(0, dbg_qen_invalid_transition);
        $dumpvars(0, dbg_qen_velocity_valid);
        $dumpvars(0, dbg_qen_ab_state);
        $dumpvars(0, dbg_qen_ext_stim_active);

      // `else
      //   $dumpfile("croc.vcd");
      //   $dumpvars(0, i_croc_soc);
      //   $dumpoff;
      `endif
    `endif
  end

  // flush waveform dump when simulation ends
  final begin
    `ifdef TRACE_WAVE
      $dumpflush;
    `endif
  end

endmodule






// // Copyright 2024 ETH Zurich and University of Bologna.
// // Solderpad Hardware License, Version 0.51, see LICENSE for details.
// // SPDX-License-Identifier: SHL-0.51
// //
// // Authors:
// // - Philippe Sauter <phsauter@iis.ee.ethz.ch>
// // - Enrico Zelioli <ezelioli@iis.ee.ethz.ch>

// `define TRACE_WAVE

// module tb_croc_soc #(
//   parameter int unsigned GpioCount = 32
// );

//   import tb_croc_pkg::*;

//   // Signals fully controlled by the VIP
//   // use VIP functions/tasks to manipulate these signals
//   logic rst_n;
//   logic sys_clk;
//   logic ref_clk;

//   logic jtag_tck;
//   logic jtag_trst_n;
//   logic jtag_tms;
//   logic jtag_tdi;
//   logic jtag_tdo;

//   logic uart_rx;
//   logic uart_tx;

//   // Signals partially controlled by the VIP
//   logic [GpioCount-1:0] gpio_in;
//   logic [GpioCount-1:0] gpio_out;
//   logic [GpioCount-1:0] gpio_out_en;

//   // Optional external GPIO stimulus driven directly by this testbench.
//   logic [GpioCount-1:0] gpio_in_ext;
//   logic [GpioCount-1:0] gpio_in_ext_oe;

//   // Signals controlled by the testbench

//   /////////////////////////////
//   //  Command Line Arguments //
//   /////////////////////////////

//   string binary_path;

//   initial begin
//     // $value$plusargs defines what to look for (here +binary=...)
//     if ($value$plusargs("binary=%s", binary_path)) begin
//       $display("Running program: %s", binary_path);
//     end else begin
//       $display("No binary path provided. Running helloworld.");
//       binary_path = "../sw/bin/helloworld.hex";
//     end
//   end

//   ////////////
//   //  VIP   //
//   ////////////
//   // Verification IP
//   // - drives clocks and resets
//   // - provides helper tasks and functions for JTAG, namely:
//   //   - jtag_load_hex: loads a hex file into the DUT's memory
//   //   - jtag_write_reg32: write 32-bit value to DUT
//   //   - jtag_read_reg32: read 32-bit value from DUT
//   //   - jtag_halt / jtag_resume: control core execution
//   //   - jtag_wait_for_eoc: wait for end of code execution (core writes non-zero to status register)
//   // - prints UART output to console (you can also write via uart_write_byte)
//   // - internal GPIO loopback for helloworld test

//   croc_vip #(
//     .GpioCount ( GpioCount )
//   ) i_vip (
//     .rst_no        ( rst_n       ),
//     .sys_clk_o     ( sys_clk     ),
//     .ref_clk_o     ( ref_clk     ),
//     .jtag_tck_o    ( jtag_tck    ),
//     .jtag_trst_no  ( jtag_trst_n ),
//     .jtag_tms_o    ( jtag_tms    ),
//     .jtag_tdi_o    ( jtag_tdi    ),
//     .jtag_tdo_i    ( jtag_tdo    ),
//     .uart_rx_o     ( uart_rx     ),
//     .uart_tx_i     ( uart_tx     ),
//     .gpio_out_en_i     ( gpio_out_en     ),
//     .gpio_out_i        ( gpio_out        ),
//     .gpio_in_ext_i     ( gpio_in_ext     ),
//     .gpio_in_ext_oe_i  ( gpio_in_ext_oe  ),
//     .gpio_in_o         ( gpio_in         )
//   );

//   ////////////
//   //  DUT   //
//   ////////////

//   `ifdef TARGET_NETLIST_YOSYS
//   \croc_soc$croc_chip.i_croc_soc i_croc_soc (
//   `else
//   croc_soc #(
//     .GpioCount ( GpioCount )
//   ) i_croc_soc (
//   `endif
//     .clk_i         ( sys_clk     ),
//     .rst_ni        ( rst_n       ),
//     .ref_clk_i     ( ref_clk     ),
//     .testmode_i    ( 1'b0        ),
//     .status_o      (             ),
//     .jtag_tck_i    ( jtag_tck    ),
//     .jtag_tdi_i    ( jtag_tdi    ),
//     .jtag_tdo_o    ( jtag_tdo    ),
//     .jtag_tms_i    ( jtag_tms    ),
//     .jtag_trst_ni  ( jtag_trst_n ),
//     .uart_rx_i     ( uart_rx     ),
//     .uart_tx_o     ( uart_tx     ),
//     .gpio_i        ( gpio_in     ),
//     .gpio_o        ( gpio_out    ),
//     .gpio_out_en_o ( gpio_out_en )
//   );

//   // Debug aliases for waveform inspection.
//   // These make GTKWave much easier than manually decoding gpio_out[31:0].
//   logic dbg_gpio0_pwm;
//   logic dbg_gpio0_out_en;
//   logic dbg_amcp_pwm_o;
//   logic [15:0] dbg_pwm_counter;
//   logic [15:0] dbg_pwm_period_active;
//   logic [15:0] dbg_pwm_duty_active;

//   // QEN debug aliases for GTKWave.
//   logic dbg_qen_a;
//   logic dbg_qen_b;
//   logic dbg_qen_z;
//   logic dbg_qen_enable;
//   logic dbg_qen_sim_input_enable;
//   logic dbg_qen_index_reset_enable;
//   logic dbg_qen_direction;
//   logic dbg_qen_index_seen;
//   logic dbg_qen_invalid_transition;
//   logic dbg_qen_velocity_valid;
//   logic [1:0] dbg_qen_ab_state;
//   logic [2:0] dbg_qen_sim_input;
//   logic [31:0] dbg_qen_error_count;
//   logic signed [31:0] dbg_qen_position;
//   logic signed [31:0] dbg_qen_velocity;
//   logic signed [31:0] dbg_qen_delta;
//   logic signed [31:0] dbg_qen_index_position;
//   logic dbg_qen_ext_stim_active;

//     // Debug aliases for GTKWave inspection in comparison between software and hardware.
//   logic dbg_gpio1_sw_marker;
//   logic dbg_gpio2_hw_marker;
//   assign dbg_gpio1_sw_marker = gpio_out[1];
//   assign dbg_gpio2_hw_marker = gpio_out[2];

//   assign dbg_gpio0_pwm         = gpio_out[0];
//   assign dbg_gpio0_out_en      = gpio_out_en[0];
//   assign dbg_amcp_pwm_o        = i_croc_soc.i_user.i_user_amcp.pwm_o;
//   assign dbg_pwm_counter       = i_croc_soc.i_user.i_user_amcp.i_pwm_core.counter_o;
//   assign dbg_pwm_period_active = i_croc_soc.i_user.i_user_amcp.i_pwm_core.period_active_o;
//   assign dbg_pwm_duty_active   = i_croc_soc.i_user.i_user_amcp.i_pwm_core.duty_active_o;

//   assign dbg_qen_a                  = i_croc_soc.i_user.i_user_amcp.qen_a;
//   assign dbg_qen_b                  = i_croc_soc.i_user.i_user_amcp.qen_b;
//   assign dbg_qen_z                  = i_croc_soc.i_user.i_user_amcp.qen_z;
//   assign dbg_qen_enable             = i_croc_soc.i_user.i_user_amcp.qen_enable_q;
//   assign dbg_qen_sim_input_enable   = i_croc_soc.i_user.i_user_amcp.qen_sim_input_enable_q;
//   assign dbg_qen_index_reset_enable = i_croc_soc.i_user.i_user_amcp.qen_index_reset_enable_q;
//   assign dbg_qen_sim_input          = i_croc_soc.i_user.i_user_amcp.qen_sim_input_q;
//   assign dbg_qen_position           = i_croc_soc.i_user.i_user_amcp.qen_position;
//   assign dbg_qen_velocity           = i_croc_soc.i_user.i_user_amcp.qen_velocity;
//   assign dbg_qen_delta              = i_croc_soc.i_user.i_user_amcp.qen_delta;
//   assign dbg_qen_index_position     = i_croc_soc.i_user.i_user_amcp.qen_index_position;
//   assign dbg_qen_error_count        = i_croc_soc.i_user.i_user_amcp.qen_error_count;
//   assign dbg_qen_direction          = i_croc_soc.i_user.i_user_amcp.qen_direction;
//   assign dbg_qen_index_seen         = i_croc_soc.i_user.i_user_amcp.qen_index_seen;
//   assign dbg_qen_invalid_transition = i_croc_soc.i_user.i_user_amcp.qen_invalid_transition;
//   assign dbg_qen_velocity_valid     = i_croc_soc.i_user.i_user_amcp.qen_velocity_valid;
//   assign dbg_qen_ab_state           = i_croc_soc.i_user.i_user_amcp.qen_ab_state;

//   localparam int unsigned QenGpioA = 1;
//   localparam int unsigned QenGpioB = 2;
//   localparam int unsigned QenGpioZ = 3;
//   localparam int unsigned QenStimHoldCycles = 4;

//   // QEN external-stimulus mode selector.
//   // Firmware writes one of these values into QEN_SAMPLE_PERIOD_OFFSET.
//   localparam logic [31:0] QenModeForwardStress = 32'h515E_0001;
//   localparam logic [31:0] QenModeReverseStress = 32'h515E_0002;
//   localparam logic [31:0] QenModeMixedDir      = 32'h515E_0003;
//   localparam logic [31:0] QenModeInvalidBurst  = 32'h515E_0004;
//   localparam logic [31:0] QenModeIndexNoReset  = 32'h515E_0005;
//   localparam logic [31:0] QenModeIndexReset    = 32'h515E_0006;

//   // QEN scaling benchmark modes. Lower 16 bits encode N in hex.
//   localparam logic [31:0] QenBench100  = 32'h515E_0064;
//   localparam logic [31:0] QenBench400  = 32'h515E_0190;
//   localparam logic [31:0] QenBench1600 = 32'h515E_0640;
//   localparam logic [31:0] QenModeMotorPlant = 32'h515E_C10D;


//   task automatic drive_qen_abz(
//     input logic a,
//     input logic b,
//     input logic z
//   );
//     gpio_in_ext_oe[QenGpioA] = 1'b1;
//     gpio_in_ext_oe[QenGpioB] = 1'b1;
//     gpio_in_ext_oe[QenGpioZ] = 1'b1;

//     gpio_in_ext[QenGpioA] = a;
//     gpio_in_ext[QenGpioB] = b;
//     gpio_in_ext[QenGpioZ] = z;

//     repeat (QenStimHoldCycles) @(posedge sys_clk);
//   endtask

//   task automatic drive_qen_forward_transitions(input int unsigned n);
//     for (int unsigned i = 0; i < n; i++) begin
//       case (i % 4)
//         0: drive_qen_abz(1'b1, 1'b0, 1'b0); // 01
//         1: drive_qen_abz(1'b1, 1'b1, 1'b0); // 11
//         2: drive_qen_abz(1'b0, 1'b1, 1'b0); // 10
//         default: drive_qen_abz(1'b0, 1'b0, 1'b0); // 00
//       endcase
//     end
//   endtask

//   task automatic drive_qen_reverse_transitions(input int unsigned n);
//     for (int unsigned i = 0; i < n; i++) begin
//       case (i % 4)
//         0: drive_qen_abz(1'b0, 1'b1, 1'b0); // 10
//         1: drive_qen_abz(1'b1, 1'b1, 1'b0); // 11
//         2: drive_qen_abz(1'b1, 1'b0, 1'b0); // 01
//         default: drive_qen_abz(1'b0, 1'b0, 1'b0); // 00
//       endcase
//     end
//   endtask



//   logic [1:0] qen_plant_ab;

//   task automatic qen_plant_drive_ab(input logic [1:0] ab);
//     begin
//       qen_plant_ab = ab;
//       // drive_qen_abz arguments are a,b,z.
//       drive_qen_abz(ab[0], ab[1], 1'b0);
//     end
//   endtask

//   task automatic qen_plant_forward_one;
//     begin
//       case (qen_plant_ab)
//         2'b00: qen_plant_drive_ab(2'b01);
//         2'b01: qen_plant_drive_ab(2'b11);
//         2'b11: qen_plant_drive_ab(2'b10);
//         default: qen_plant_drive_ab(2'b00);
//       endcase
//     end
//   endtask

//   task automatic qen_plant_reverse_one;
//     begin
//       case (qen_plant_ab)
//         2'b00: qen_plant_drive_ab(2'b10);
//         2'b10: qen_plant_drive_ab(2'b11);
//         2'b11: qen_plant_drive_ab(2'b01);
//         default: qen_plant_drive_ab(2'b00);
//       endcase
//     end
//   endtask

//   task automatic qen_plant_drive_steps(input int signed steps);
//     begin
//       if (steps > 0) begin
//         repeat (steps) begin
//           qen_plant_forward_one();
//         end
//       end else if (steps < 0) begin
//         repeat (-steps) begin
//           qen_plant_reverse_one();
//         end
//       end
//     end
//   endtask

//   task automatic run_qen_motor_plant(input int unsigned max_windows);
//     int unsigned high_count;
//     int signed effort;
//     int signed target_vel_q8;
//     int signed vel_q8;
//     int signed frac_q8;
//     int signed steps;
//     int unsigned w;
//     begin
//       $display("@%t | [QEN_PLANT] Motor plant started", $time);

//       qen_plant_ab = 2'b00;
//       vel_q8  = 0;
//       frac_q8 = 0;
//       w       = 0;

//       // Start encoder at AB=00, Z=0.
//       qen_plant_drive_ab(2'b00);

//       while (i_croc_soc.i_user.i_user_amcp.qen_enable_q &&
//              (i_croc_soc.i_user.i_user_amcp.qen_sample_period_q == QenModeMotorPlant) &&
//              ((max_windows == 0) || (w < max_windows))) begin

//         // Measure actual AMCP PWM output over one PWM period.
//         // Firmware programs PWM_PERIOD = 100.
//         high_count = 0;

//         for (int unsigned i = 0; i < 100; i++) begin
//           @(posedge sys_clk);

//           if (i_croc_soc.i_user.i_user_amcp.pwm_o) begin
//             high_count++;
//           end
//         end

//         // Simple closed-loop plant model:
//         // Measure actual PWM high_count over one PWM period.
//         //
//         // high_count = 50 -> zero motion
//         // high_count > 50 -> positive QEN position motion
//         // high_count < 50 -> negative QEN position motion
//         //
//         // We intentionally generate at most one encoder transition every
//         // 32 PWM windows. This makes plant dynamics slower than the CPU
//         // control loop and avoids violent overshoot.
//         effort = int'(high_count) - 50;

//         if ((w < 20) || ((w % 512) == 0)) begin
//           $display("@%t | [PDBG] w=%0d high=%0d effort=%0d ab=%b",
//                    $time, w, high_count, effort, qen_plant_ab);
//         end

//         if ((w % 64) == 0) begin
//           if (effort > 6) begin
//             // Positive PWM effort should increase QEN position.
//             qen_plant_forward_one();
//           end else if (effort < -6) begin
//             // Negative PWM effort should decrease QEN position.
//             qen_plant_reverse_one();
//           end
//         end

//         w++;
//       end

//       $display("@%t | [QEN_PLANT] Motor plant stopped after %0d windows", $time, w);
//     end
//   endtask

//   task automatic drive_qen_invalid_burst(input int unsigned n);
//     // Starting from 00, alternate 00 <-> 11.
//     // Each transition changes both A and B, so every transition is invalid.
//     for (int unsigned i = 0; i < n; i++) begin
//       if ((i % 2) == 0) begin
//         drive_qen_abz(1'b1, 1'b1, 1'b0); // 11
//       end else begin
//         drive_qen_abz(1'b0, 1'b0, 1'b0); // 00
//       end
//     end
//   endtask

//   initial begin
//     gpio_in_ext             = '0;
//     gpio_in_ext_oe          = '0;
//     dbg_qen_ext_stim_active = 1'b0;
//   end

//   // External encoder stimulus.
//   // This block stays idle for normal tests. It only runs when firmware enables
//   // QEN with sim_input_enable = 0.
//   initial begin
//     @(posedge rst_n);

//     forever begin
//       wait (i_croc_soc.i_user.i_user_amcp.qen_enable_q &&
//             !i_croc_soc.i_user.i_user_amcp.qen_sim_input_enable_q);

//       dbg_qen_ext_stim_active = 1'b1;

//       // Hold initial encoder state long enough for QEN to initialize prev_ab.
//       drive_qen_abz(1'b0, 1'b0, 1'b0);
//       repeat (100) @(posedge sys_clk);

//       unique case (i_croc_soc.i_user.i_user_amcp.qen_sample_period_q)

//         QenBench100: begin
//           // Expected: benchmark position = +100, error_count = 0.
//           drive_qen_forward_transitions(100);
//           repeat (500) @(posedge sys_clk);
//         end

//         QenBench400: begin
//           // Expected: benchmark position = +400, error_count = 0.
//           drive_qen_forward_transitions(400);
//           repeat (500) @(posedge sys_clk);
//         end

//         QenBench1600: begin
//           // Expected: benchmark position = +1600, error_count = 0.
//           drive_qen_forward_transitions(1600);
//           repeat (500) @(posedge sys_clk);
//         end

//         QenModeMotorPlant: begin
//           // Closed-loop PID demo:
//           // actual hardware PWM output -> testbench motor model -> external QEN GPIO A/B.
//           run_qen_motor_plant(0);
//           repeat (500) @(posedge sys_clk);
//         end

//         QenModeForwardStress: begin
//           // Expected: position = +400, error_count = 0.
//           drive_qen_forward_transitions(400);
//           repeat (500) @(posedge sys_clk);
//         end

//         QenModeReverseStress: begin
//           // Expected: position = -160, error_count = 0.
//           drive_qen_reverse_transitions(160);
//           repeat (500) @(posedge sys_clk);
//         end

//         QenModeMixedDir: begin
//           // Expected: +128 - 48 = +80, error_count = 0.
//           drive_qen_forward_transitions(128);
//           drive_qen_reverse_transitions(48);
//           repeat (500) @(posedge sys_clk);
//         end

//         QenModeInvalidBurst: begin
//           // Expected: position = 0, error_count = 16.
//           drive_qen_invalid_burst(16);
//           repeat (500) @(posedge sys_clk);
//         end

//         QenModeIndexNoReset: begin
//           // Expected: move to 40, capture index_position=40,
//           // then continue to final position 60.
//           drive_qen_forward_transitions(40);
//           drive_qen_abz(1'b0, 1'b0, 1'b1); // Z high at position 40
//           drive_qen_abz(1'b0, 1'b0, 1'b0); // Z low
//           drive_qen_forward_transitions(20);
//           repeat (500) @(posedge sys_clk);
//         end

//         QenModeIndexReset: begin
//           // Firmware enables index_reset.
//           // Expected: move to 40, capture index_position=40,
//           // reset live position to 0, then move 20 more -> final position 20.
//           drive_qen_forward_transitions(40);
//           drive_qen_abz(1'b0, 1'b0, 1'b1); // Z high at position 40
//           drive_qen_abz(1'b0, 1'b0, 1'b0); // Z low
//           drive_qen_forward_transitions(20);
//           repeat (500) @(posedge sys_clk);
//         end

//         default: begin
//           // Legacy directed demo mode:
//           // forward +4, index, one invalid jump.
//           drive_qen_forward_transitions(4);
//           drive_qen_abz(1'b0, 1'b0, 1'b1);
//           drive_qen_abz(1'b0, 1'b0, 1'b0);
//           drive_qen_abz(1'b1, 1'b1, 1'b0);
//           repeat (200) @(posedge sys_clk);
//         end

//       endcase

//       dbg_qen_ext_stim_active = 1'b0;

//       wait (!i_croc_soc.i_user.i_user_amcp.qen_enable_q ||
//              i_croc_soc.i_user.i_user_amcp.qen_sim_input_enable_q);
//     end
//   end

  
//   /////////////////
//   //  Testbench  //
//   /////////////////

//   logic [31:0] tb_data;

//   initial begin
//     $timeformat(-9, 0, "ns", 12); // 1: scale (ns=-9), 2: decimals, 3: suffix, 4: print-field width

//     // wait for reset
//     #ClkPeriodSys;

//     // init jtag
//     i_vip.jtag_init();

//     // write test value to sram
//     i_vip.jtag_write_reg32(SramBaseAddr, 32'h1234_5678, 1'b1);

//     // load binary to sram
//     i_vip.jtag_load_hex(binary_path);

//     // wake core from WFI by writing to CLINT msip
//     $display("@%t | [CORE] Waking core via CLINT msip", $time);
//     i_vip.jtag_write_reg32(ClintBaseAddr, 32'h1);

//     // halt core
//     i_vip.jtag_halt();

//     // resume core
//     i_vip.jtag_resume();

//     // wait for non-zero return value (written into core status register)
//     $display("@%t | [CORE] Wait for end of code...", $time);
//     i_vip.jtag_wait_for_eoc(tb_data);
    
//     // finish simulation
//     repeat(50) @(posedge sys_clk);
//     $finish();
//   end

//   ////////////////
//   //  Waveform  //
//   ////////////////
//   // start waveform dump at time 0, independent of stimuli
//   initial begin
//     `ifdef TRACE_WAVE
//       `ifdef VERILATOR
//         $dumpfile("croc.fst");
//         $dumpvars(1, i_croc_soc);

//         // Also dump selected scalar debug aliases from the testbench.
//         $dumpvars(0, dbg_gpio0_pwm);
//         $dumpvars(0, dbg_gpio0_out_en);
//         $dumpvars(0, dbg_amcp_pwm_o);
//         $dumpvars(0, dbg_pwm_counter);
//         $dumpvars(0, dbg_pwm_period_active);
//         $dumpvars(0, dbg_pwm_duty_active);
//         $dumpvars(0, dbg_gpio1_sw_marker);
//         $dumpvars(0, dbg_gpio2_hw_marker);

//         $dumpvars(0, dbg_qen_a);
//         $dumpvars(0, dbg_qen_b);
//         $dumpvars(0, dbg_qen_z);
//         $dumpvars(0, dbg_qen_enable);
//         $dumpvars(0, dbg_qen_sim_input_enable);
//         $dumpvars(0, dbg_qen_index_reset_enable);
//         $dumpvars(0, dbg_qen_sim_input);
//         $dumpvars(0, dbg_qen_position);
//         $dumpvars(0, dbg_qen_velocity);
//         $dumpvars(0, dbg_qen_delta);
//         $dumpvars(0, dbg_qen_index_position);
//         $dumpvars(0, dbg_qen_error_count);
//         $dumpvars(0, dbg_qen_direction);
//         $dumpvars(0, dbg_qen_index_seen);
//         $dumpvars(0, dbg_qen_invalid_transition);
//         $dumpvars(0, dbg_qen_velocity_valid);
//         $dumpvars(0, dbg_qen_ab_state);
//         $dumpvars(0, dbg_qen_ext_stim_active);

//       `else
//         $dumpfile("croc.vcd");
//         $dumpvars(0, i_croc_soc);
//         $dumpoff;
//       `endif
//     `endif
//   end

//   // flush waveform dump when simulation ends
//   final begin
//     `ifdef TRACE_WAVE
//       $dumpflush;
//     `endif
//   end

// endmodule
