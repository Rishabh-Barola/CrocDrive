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

    // wait for non-zero return value (written into core status register)
    $display("@%t | [CORE] Wait for end of code...", $time);
    i_vip.jtag_wait_for_eoc(tb_data);

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

      `else
        $dumpfile("croc.vcd");
        $dumpvars(1, i_croc_soc);
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
