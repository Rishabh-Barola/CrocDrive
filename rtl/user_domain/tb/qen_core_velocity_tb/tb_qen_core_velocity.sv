`timescale 1ns/1ps

module tb_qen_core_velocity;

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

  task automatic drive_ab(input logic [1:0] ab);
    // QEN convention: ab = {B,A}
    @(negedge clk_i);
    b_i = ab[1];
    a_i = ab[0];
    z_i = 1'b0;
    @(posedge clk_i);
    #1;
  endtask

  task automatic hold_ab(input logic [1:0] ab, input int unsigned cycles);
    for (int unsigned i = 0; i < cycles; i++) begin
      drive_ab(ab);
    end
  endtask

  task automatic drive_forward(input int unsigned n);
    for (int unsigned i = 0; i < n; i++) begin
      case (i % 4)
        0: drive_ab(2'b01); // 00 -> 01
        1: drive_ab(2'b11); // 01 -> 11
        2: drive_ab(2'b10); // 11 -> 10
        default: drive_ab(2'b00); // 10 -> 00
      endcase
    end
  endtask

  task automatic drive_reverse(input int unsigned n);
    for (int unsigned i = 0; i < n; i++) begin
      case (i % 4)
        0: drive_ab(2'b10); // 00 -> 10
        1: drive_ab(2'b11); // 10 -> 11
        2: drive_ab(2'b01); // 11 -> 01
        default: drive_ab(2'b00); // 01 -> 00
      endcase
    end
  endtask

  task automatic wait_velocity_valid;
    begin
      if (!velocity_valid_o) begin
        do begin
          @(posedge clk_i);
          #1;
        end while (!velocity_valid_o);
      end
    end
  endtask

  task automatic expect_sample(
    input int signed exp_delta,
    input int signed exp_velocity,
    input int signed exp_position,
    input string label
  );
    begin
      wait_velocity_valid();

      if (delta_o !== exp_delta) begin
        $display("[FAIL] %s: expected delta %0d, got %0d",
                 label, exp_delta, delta_o);
        $fatal(1);
      end

      if (velocity_o !== exp_velocity) begin
        $display("[FAIL] %s: expected velocity %0d, got %0d",
                 label, exp_velocity, velocity_o);
        $fatal(1);
      end

      if (position_o !== exp_position) begin
        $display("[FAIL] %s: expected position %0d, got %0d",
                 label, exp_position, position_o);
        $fatal(1);
      end

      $display("[PASS] %s: delta=%0d velocity=%0d position=%0d",
               label, delta_o, velocity_o, position_o);
    end
  endtask

  task automatic reset_qen;
    begin
      enable_i = 1'b0;
      clear_position_i = 1'b0;
      clear_error_i = 1'b0;
      index_reset_enable_i = 1'b0;
      sample_period_i = 32'd8;

      a_i = 1'b0;
      b_i = 1'b0;
      z_i = 1'b0;

      rst_ni = 1'b0;
      repeat (5) @(posedge clk_i);
      rst_ni = 1'b1;
      repeat (5) @(posedge clk_i);

      enable_i = 1'b1;

      // Let QEN establish initial AB=00 and align to one sample boundary.
      hold_ab(2'b00, 2);
      wait_velocity_valid();
    end
  endtask

  initial begin
    $dumpfile("qen_core_velocity.fst");
    $dumpvars(0, tb_qen_core_velocity);
  end

  initial begin
    $display("[TB] QEN velocity/delta test start");

    reset_qen();

    // Case 1: exactly 8 forward transitions in one 8-cycle sample window.
    drive_forward(8);
    expect_sample(+8, +8, +8, "forward_8_transitions");

    // Case 2: another 8 forward transitions.
    drive_forward(8);
    expect_sample(+8, +8, +16, "forward_8_transitions_again");

    // Case 3: no movement for one full sample window.
    hold_ab(2'b00, 8);
    expect_sample(0, 0, +16, "idle_window");

    // Case 4: exactly 8 reverse transitions.
    drive_reverse(8);
    expect_sample(-8, -8, +8, "reverse_8_transitions");

    // Reset and align again for mixed-window test.
    reset_qen();

    // Case 5: within one sample window:
    // +4 forward transitions, then -2 reverse transitions, then 2 idle cycles.
    // Net delta = +2.
    drive_forward(4);
    drive_reverse(2);
    hold_ab(2'b11, 2);
    expect_sample(+2, +2, +2, "mixed_plus4_minus2");

    // Reset and test invalid transitions.
    reset_qen();

    // Case 6: invalid 00->11 and 11->00. Position stays 0.
    drive_ab(2'b11);
    drive_ab(2'b00);
    hold_ab(2'b00, 6);
    expect_sample(0, 0, 0, "invalid_transitions_no_motion");

    if (error_count_o !== 32'd2) begin
      $display("[FAIL] invalid transitions: expected error_count=2, got %0d",
               error_count_o);
      $fatal(1);
    end

    $display("[PASS] invalid transitions: error_count=%0d", error_count_o);

    $display("[TB] QEN velocity/delta test PASSED");
    $finish;
  end

endmodule
