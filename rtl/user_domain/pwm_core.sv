// Simple programmable PWM core.
// No OBI here: this is pure PWM datapath/control logic.

module pwm_core #(
  parameter int unsigned Width = 16
) (
  input  logic             clk_i,
  input  logic             rst_ni,

  input  logic             enable_i,
  input  logic             polarity_i,

  input  logic [Width-1:0] period_cfg_i,
  input  logic [Width-1:0] duty_cfg_i,

  output logic             pwm_o,
  output logic [Width-1:0] counter_o,
  output logic [Width-1:0] period_active_o,
  output logic [Width-1:0] duty_active_o,
  output logic             period_done_o,
  output logic             period_zero_o
);

  logic [Width-1:0] counter_q;
  logic [Width-1:0] period_active_q;
  logic [Width-1:0] duty_active_q;

  logic [Width-1:0] duty_clamped;
  logic             pwm_raw;

  always_comb begin
    if (period_cfg_i == '0) begin
      duty_clamped = '0;
    end else if (duty_cfg_i >= period_cfg_i) begin
      duty_clamped = period_cfg_i;
    end else begin
      duty_clamped = duty_cfg_i;
    end
  end

  assign period_done_o = enable_i &&
                         (period_active_q != '0) &&
                         (counter_q == (period_active_q - {{(Width-1){1'b0}}, 1'b1}));

  // This now means: PWM is enabled while the configured period is invalid.
  assign period_zero_o = enable_i &&
                         (period_active_q == '0) &&
                         (period_cfg_i == '0);

  always_ff @(posedge clk_i or negedge rst_ni) begin
    if (!rst_ni) begin
      counter_q       <= '0;
      period_active_q <= '0;
      duty_active_q   <= '0;
    end else begin

      if (!enable_i) begin
        // While disabled, keep active values preloaded with the latest config.
        // This avoids a wrong old-duty pulse when PWM is enabled again.
        counter_q       <= '0;
        period_active_q <= period_cfg_i;
        duty_active_q   <= duty_clamped;

      end else if (period_active_q == '0) begin
        // Allows recovery if period was previously zero and software writes a valid period.
        counter_q       <= '0;
        period_active_q <= period_cfg_i;
        duty_active_q   <= duty_clamped;

      end else if (period_done_o) begin
        // Period boundary: safely latch new config and restart counter.
        counter_q       <= '0;
        period_active_q <= period_cfg_i;
        duty_active_q   <= duty_clamped;

      end else begin
        counter_q <= counter_q + {{(Width-1){1'b0}}, 1'b1};
      end
    end
  end

  assign pwm_raw = enable_i &&
                   (period_active_q != '0) &&
                   (counter_q < duty_active_q);

  always_comb begin
    if (!enable_i || (period_active_q == '0)) begin
      pwm_o = 1'b0;
    end else begin
      pwm_o = polarity_i ? ~pwm_raw : pwm_raw;
    end
  end

  assign counter_o       = counter_q;
  assign period_active_o = period_active_q;
  assign duty_active_o   = duty_active_q;

endmodule