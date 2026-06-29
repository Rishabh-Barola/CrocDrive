`timescale 1ns/1ps

module tb_qen_core_velocity_stress;

  logic clk_i;
  logic rst_ni;

  logic enable_i;
  logic clear_position_i;
  logic clear_error_i;
  logic index_reset_enable_i;
  logic [31:0] sample_period_i;

  logic a_i;
  logic b_i;
  logic z_i;

  logic signed [31:0] position_o;
  logic signed [31:0] velocity_o;
  logic signed [31:0] delta_o;
  logic direction_o;
  logic index_seen_o;
  logic signed [31:0] index_position_o;
  logic [31:0] error_count_o;
  logic invalid_transition_o;
  logic velocity_valid_o;
  logic [1:0] ab_state_o;

  qen_core i_dut (
    .clk_i,
    .rst_ni,

    .enable_i,
    .clear_position_i,
    .clear_error_i,
    .index_reset_enable_i,
    .sample_period_i,

    .a_i,
    .b_i,
    .z_i,

    .position_o,
    .velocity_o,
    .delta_o,
    .direction_o,
    .index_seen_o,
    .index_position_o,
    .error_count_o,
    .invalid_transition_o,
    .velocity_valid_o,
    .ab_state_o
  );

  initial begin
    clk_i = 1'b0;
    forever #5 clk_i = ~clk_i; // 100 MHz
  end

  // Golden model state used by the testbench.
  logic [1:0] curr_ab;
  int signed exp_pos;
  int signed sample_base_pos;
  int unsigned exp_err;

  int unsigned sample_count;
  int unsigned pos_sample_count;
  int unsigned neg_sample_count;
  int unsigned zero_sample_count;
  int unsigned odd_sample_count;
  int unsigned invalid_event_count;

  task automatic check_sample_if_valid(input string tag);
    int signed exp_delta;
    begin
      if (velocity_valid_o) begin
        exp_delta = exp_pos - sample_base_pos;

        if (delta_o !== exp_delta) begin
          $display("[FAIL] %s sample %0d: expected delta %0d, got %0d",
                   tag, sample_count, exp_delta, delta_o);
          $fatal(1);
        end

        if (velocity_o !== exp_delta) begin
          $display("[FAIL] %s sample %0d: expected velocity %0d, got %0d",
                   tag, sample_count, exp_delta, velocity_o);
          $fatal(1);
        end

        if (position_o !== exp_pos) begin
          $display("[FAIL] %s sample %0d: expected position %0d, got %0d",
                   tag, sample_count, exp_pos, position_o);
          $fatal(1);
        end

        if (error_count_o !== exp_err) begin
          $display("[FAIL] %s sample %0d: expected error_count %0d, got %0d",
                   tag, sample_count, exp_err, error_count_o);
          $fatal(1);
        end

        $display("[SAMPLE] %-24s sample=%0d period=%0d delta=%0d velocity=%0d position=%0d errors=%0d",
                 tag, sample_count, sample_period_i, delta_o, velocity_o, position_o, error_count_o);

        if (exp_delta > 0) begin
          pos_sample_count++;
        end else if (exp_delta < 0) begin
          neg_sample_count++;
        end else begin
          zero_sample_count++;
        end

        if ((exp_delta % 2) != 0) begin
          odd_sample_count++;
        end

        sample_base_pos = exp_pos;
        sample_count++;
      end
    end
  endtask

  task automatic drive_current_ab(input string tag);
    begin
      @(negedge clk_i);
      b_i = curr_ab[1];
      a_i = curr_ab[0];
      z_i = 1'b0;

      @(posedge clk_i);
      #1;
      check_sample_if_valid(tag);
    end
  endtask

  task automatic hold_one(input string tag);
    begin
      drive_current_ab(tag);
    end
  endtask

  task automatic forward_one(input string tag);
    begin
      case (curr_ab)
        2'b00: curr_ab = 2'b01;
        2'b01: curr_ab = 2'b11;
        2'b11: curr_ab = 2'b10;
        default: curr_ab = 2'b00;
      endcase

      exp_pos++;
      drive_current_ab(tag);
    end
  endtask

  task automatic reverse_one(input string tag);
    begin
      case (curr_ab)
        2'b00: curr_ab = 2'b10;
        2'b10: curr_ab = 2'b11;
        2'b11: curr_ab = 2'b01;
        default: curr_ab = 2'b00;
      endcase

      exp_pos--;
      drive_current_ab(tag);
    end
  endtask

  task automatic invalid_one(input string tag);
    begin
      // Toggle both A and B, creating 00<->11 or 01<->10.
      // This should increment error_count and should not change position.
      case (curr_ab)
        2'b00: curr_ab = 2'b11;
        2'b11: curr_ab = 2'b00;
        2'b01: curr_ab = 2'b10;
        default: curr_ab = 2'b01;
      endcase

      exp_err++;
      invalid_event_count++;
      drive_current_ab(tag);
    end
  endtask

  task automatic run_window(
    input string tag,
    input int unsigned fwd_count,
    input int unsigned rev_count,
    input int unsigned inv_count
  );
    int unsigned used;
    begin
      used = fwd_count + rev_count + inv_count;

      if (used > sample_period_i) begin
        $display("[FAIL] %s: window uses %0d cycles > sample_period %0d",
                 tag, used, sample_period_i);
        $fatal(1);
      end

      repeat (fwd_count) begin
        forward_one(tag);
      end

      repeat (rev_count) begin
        reverse_one(tag);
      end

      repeat (inv_count) begin
        invalid_one(tag);
      end

      repeat (sample_period_i - used) begin
        hold_one(tag);
      end
    end
  endtask

  task automatic align_to_sample_boundary(input string tag);
    int unsigned old_count;
    begin
      old_count = sample_count;

      while (sample_count == old_count) begin
        hold_one(tag);
      end

      // check_sample_if_valid already updated sample_base_pos.
      $display("[ALIGN] %s: aligned at sample_count=%0d position=%0d",
               tag, sample_count, exp_pos);
    end
  endtask

  task automatic configure_qen(input int unsigned period);
    begin
      rst_ni = 1'b0;

      enable_i = 1'b0;
      clear_position_i = 1'b0;
      clear_error_i = 1'b0;
      index_reset_enable_i = 1'b0;
      sample_period_i = period;

      curr_ab = 2'b00;
      a_i = 1'b0;
      b_i = 1'b0;
      z_i = 1'b0;

      exp_pos = 0;
      sample_base_pos = 0;
      exp_err = 0;

      repeat (5) @(posedge clk_i);

      rst_ni = 1'b1;
      repeat (5) @(posedge clk_i);

      enable_i = 1'b1;

      align_to_sample_boundary($sformatf("period_%0d_align", period));
    end
  endtask

  initial begin
    $dumpfile("qen_core_velocity_stress.fst");
    $dumpvars(0, tb_qen_core_velocity_stress);
  end

  initial begin
    sample_count = 0;
    pos_sample_count = 0;
    neg_sample_count = 0;
    zero_sample_count = 0;
    odd_sample_count = 0;
    invalid_event_count = 0;

    $display("[TB] QEN velocity/delta stress test start");

    // ----------------------------------------------------------------------
    // Test 1: fractional average positive speed.
    // sample_period = 13.
    // Alternate 5 and 6 forward transitions per sample window.
    // This represents an average of 5.5 counts/window without losing position.
    // ----------------------------------------------------------------------
    configure_qen(13);

    run_window("frac_fwd_5", 5, 0, 0);
    run_window("frac_fwd_6", 6, 0, 0);
    run_window("frac_fwd_5", 5, 0, 0);
    run_window("frac_fwd_6", 6, 0, 0);
    run_window("frac_fwd_5", 5, 0, 0);
    run_window("frac_fwd_6", 6, 0, 0);

    if (exp_pos !== 33) begin
      $display("[FAIL] fractional forward: expected cumulative position 33, got %0d", exp_pos);
      $fatal(1);
    end

    $display("[PASS] fractional forward average: total position=%0d over 6 windows, average delta=5.5", exp_pos);

    // ----------------------------------------------------------------------
    // Test 2: odd mixed windows with direction reversals and invalid jumps.
    // sample_period = 17.
    // Windows include +7-4=+3, -9+2=-7, +1-1+5-2=+3.
    // Invalid jumps should increase error count but not delta.
    // ----------------------------------------------------------------------
    configure_qen(17);

    run_window("mixed_p17_plus3_inv2", 7, 4, 2);
    run_window("mixed_p17_minus7_inv1", 2, 9, 1);
    run_window("mixed_p17_plus3", 6, 3, 0);

    // ----------------------------------------------------------------------
    // Test 3: larger odd windows and zero-motion window.
    // sample_period = 29.
    // Exercises large odd delta, large negative delta, and zero delta.
    // ----------------------------------------------------------------------
    configure_qen(29);

    run_window("large_p29_plus13", 19, 6, 0);
    run_window("large_p29_minus13_inv4", 4, 17, 4);
    run_window("large_p29_idle", 0, 0, 0);

    // ----------------------------------------------------------------------
    // Test 4: maximum transition density for this test style.
    // sample_period = 31.
    // Every cycle is a valid transition.
    // ----------------------------------------------------------------------
    configure_qen(31);

    run_window("dense_p31_plus31", 31, 0, 0);
    run_window("dense_p31_minus31", 0, 31, 0);

    // Final coverage checks.
    if (sample_count < 15) begin
      $display("[FAIL] expected many velocity samples, saw only %0d", sample_count);
      $fatal(1);
    end

    if (pos_sample_count == 0) begin
      $display("[FAIL] did not observe positive velocity sample");
      $fatal(1);
    end

    if (neg_sample_count == 0) begin
      $display("[FAIL] did not observe negative velocity sample");
      $fatal(1);
    end

    if (zero_sample_count == 0) begin
      $display("[FAIL] did not observe zero velocity sample");
      $fatal(1);
    end

    if (odd_sample_count == 0) begin
      $display("[FAIL] did not observe odd/non-round velocity sample");
      $fatal(1);
    end

    if (invalid_event_count == 0) begin
      $display("[FAIL] did not exercise invalid transitions");
      $fatal(1);
    end

    $display("[SUMMARY] samples=%0d positive=%0d negative=%0d zero=%0d odd=%0d invalid_events=%0d",
             sample_count, pos_sample_count, neg_sample_count,
             zero_sample_count, odd_sample_count, invalid_event_count);

    $display("[TB] QEN velocity/delta stress test PASSED");
    $finish;
  end

endmodule
