// Quadrature Encoder Interface core for AMCP.
//
// Decodes A/B quadrature transitions into position, direction, velocity,
// index position, and invalid-transition error count.
//
// State encoding uses {B,A}:
//   forward: 00 -> 01 -> 11 -> 10 -> 00
//   reverse: 00 -> 10 -> 11 -> 01 -> 00

module qen_core #(
  parameter int unsigned PosWidth    = 32,
  parameter int unsigned SampleWidth = 32
) (
  input  logic clk_i,
  input  logic rst_ni,

  input  logic enable_i,
  input  logic clear_position_i,
  input  logic clear_error_i,
  input  logic index_reset_enable_i,

  input  logic [SampleWidth-1:0] sample_period_i,

  input  logic a_i,
  input  logic b_i,
  input  logic z_i,

  output logic signed [PosWidth-1:0] position_o,
  output logic signed [PosWidth-1:0] velocity_o,
  output logic signed [PosWidth-1:0] delta_o,
  output logic direction_o,
  output logic index_seen_o,
  output logic signed [PosWidth-1:0] index_position_o,
  output logic [31:0] error_count_o,
  output logic invalid_transition_o,
  output logic velocity_valid_o,
  output logic [1:0] ab_state_o
);

  logic enabled_q;

  logic [1:0] prev_ab_q;
  logic [1:0] curr_ab;

  logic z_q;

  logic signed [PosWidth-1:0] position_q;
  logic signed [PosWidth-1:0] velocity_q;
  logic signed [PosWidth-1:0] delta_q;
  logic signed [PosWidth-1:0] sample_position_q;
  logic signed [PosWidth-1:0] index_position_q;

  logic direction_q;
  logic index_seen_q;
  logic [31:0] error_count_q;

  logic invalid_transition_q;
  logic velocity_valid_q;

  logic [SampleWidth-1:0] sample_counter_q;
  logic [SampleWidth-1:0] sample_period_eff;

  logic signed [1:0] step_delta;
  logic transition_valid;
  logic transition_invalid;

  logic signed [PosWidth-1:0] step_ext;
  logic signed [PosWidth-1:0] position_after_step;
  logic signed [PosWidth-1:0] sample_delta;

  logic sample_now;
  logic z_rise;

  assign curr_ab = {b_i, a_i};

  always_comb begin
    step_delta         = 2'sd0;
    transition_valid   = 1'b0;
    transition_invalid = 1'b0;

    unique case ({prev_ab_q, curr_ab})
      // Forward: 00 -> 01 -> 11 -> 10 -> 00
      4'b0001,
      4'b0111,
      4'b1110,
      4'b1000: begin
        step_delta       = 2'sd1;
        transition_valid = 1'b1;
      end

      // Reverse: 00 -> 10 -> 11 -> 01 -> 00
      4'b0010,
      4'b1011,
      4'b1101,
      4'b0100: begin
        step_delta       = -2'sd1;
        transition_valid = 1'b1;
      end

      // No movement
      4'b0000,
      4'b0101,
      4'b1010,
      4'b1111: begin
        step_delta       = 2'sd0;
        transition_valid = 1'b0;
      end

      // Illegal two-bit jumps
      default: begin
        step_delta         = 2'sd0;
        transition_invalid = 1'b1;
      end
    endcase
  end

  assign step_ext = {{(PosWidth-2){step_delta[1]}}, step_delta};

  assign position_after_step = transition_valid ? (position_q + step_ext) : position_q;

  assign sample_period_eff = (sample_period_i == '0)
                           ? {{(SampleWidth-1){1'b0}}, 1'b1}
                           : sample_period_i;

  assign sample_now   = sample_counter_q >= (sample_period_eff - {{(SampleWidth-1){1'b0}}, 1'b1});
  assign sample_delta = position_after_step - sample_position_q;
  assign z_rise       = z_i & ~z_q;

  always_ff @(posedge clk_i or negedge rst_ni) begin
    if (!rst_ni) begin
      enabled_q             <= 1'b0;
      prev_ab_q             <= 2'b00;
      z_q                   <= 1'b0;

      position_q            <= '0;
      velocity_q            <= '0;
      delta_q               <= '0;
      sample_position_q     <= '0;
      index_position_q      <= '0;

      direction_q           <= 1'b1;
      index_seen_q          <= 1'b0;
      error_count_q         <= '0;

      invalid_transition_q  <= 1'b0;
      velocity_valid_q      <= 1'b0;
      sample_counter_q      <= '0;
    end else begin
      invalid_transition_q <= 1'b0;
      velocity_valid_q     <= 1'b0;
      z_q                  <= z_i;

      if (clear_error_i) begin
        error_count_q <= '0;
      end

      if (clear_position_i) begin
        enabled_q         <= enable_i;
        prev_ab_q         <= curr_ab;

        position_q        <= '0;
        velocity_q        <= '0;
        delta_q           <= '0;
        sample_position_q <= '0;
        index_position_q  <= '0;
        index_seen_q      <= 1'b0;
        sample_counter_q  <= '0;
      end else if (!enable_i) begin
        enabled_q        <= 1'b0;
        prev_ab_q        <= curr_ab;
        sample_counter_q <= '0;
      end else begin
        enabled_q <= 1'b1;

        // First enabled cycle only initializes the previous A/B state.
        if (!enabled_q) begin
          prev_ab_q         <= curr_ab;
          sample_position_q <= position_q;
          sample_counter_q  <= '0;
        end else begin
          prev_ab_q <= curr_ab;

          if (transition_valid) begin
            position_q  <= position_after_step;
            direction_q <= (step_delta == 2'sd1);
          end

          if (transition_invalid) begin
            invalid_transition_q <= 1'b1;
            if (!clear_error_i) begin
              error_count_q <= error_count_q + 32'd1;
            end
          end

          if (z_rise) begin
            index_seen_q     <= 1'b1;
            index_position_q <= position_after_step;

            if (index_reset_enable_i) begin
              position_q        <= '0;
              velocity_q        <= '0;
              delta_q           <= '0;
              sample_position_q <= '0;
              sample_counter_q  <= '0;
            end
          end else if (sample_now) begin
            delta_q           <= sample_delta;
            velocity_q        <= sample_delta;
            sample_position_q <= position_after_step;
            sample_counter_q  <= '0;
            velocity_valid_q  <= 1'b1;
          end else begin
            sample_counter_q <= sample_counter_q + {{(SampleWidth-1){1'b0}}, 1'b1};
          end
        end
      end
    end
  end

  assign position_o           = position_q;
  assign velocity_o           = velocity_q;
  assign delta_o              = delta_q;
  assign direction_o          = direction_q;
  assign index_seen_o         = index_seen_q;
  assign index_position_o     = index_position_q;
  assign error_count_o        = error_count_q;
  assign invalid_transition_o = invalid_transition_q;
  assign velocity_valid_o     = velocity_valid_q;
  assign ab_state_o           = curr_ab;

endmodule
