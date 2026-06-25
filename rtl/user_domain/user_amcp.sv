// Advanced Motor Control Peripheral, first version.
// Currently implements only one PWM channel and GPIO[0] alternate-function routing.

module user_amcp #(
  parameter int unsigned       GpioCount = 16,
  parameter int unsigned       PwmWidth  = 16,
  parameter obi_pkg::obi_cfg_t ObiCfg    = obi_pkg::ObiDefaultConfig,
  parameter type               obi_req_t = logic,
  parameter type               obi_rsp_t = logic
) (
  input  logic clk_i,
  input  logic rst_ni,

  input  obi_req_t obi_req_i,
  output obi_rsp_t obi_rsp_o,

  input  logic [GpioCount-1:0] gpio_in_sync_i,

  output logic [GpioCount-1:0] amcp_gpio_o,
  output logic [GpioCount-1:0] amcp_gpio_out_en_o,
  output logic [GpioCount-1:0] amcp_gpio_override_o
);

  localparam logic [31:0] AmcpId      = 32'h414D4350; // "AMCP"
  localparam logic [31:0] AmcpVersion = 32'h00000001;

  localparam int unsigned QenWidth = 32;

  localparam logic [5:0] RegAmcpId           = 6'h00; // 0x000
  localparam logic [5:0] RegAmcpVersion      = 6'h01; // 0x004
  localparam logic [5:0] RegAmcpPinmux       = 6'h02; // 0x008
  localparam logic [5:0] RegAmcpStatus       = 6'h03; // 0x00C
  localparam logic [5:0] RegPwmCtrl          = 6'h04; // 0x010
  localparam logic [5:0] RegPwmPeriod        = 6'h05; // 0x014
  localparam logic [5:0] RegPwmDuty          = 6'h06; // 0x018
  localparam logic [5:0] RegPwmCounter       = 6'h07; // 0x01C
  localparam logic [5:0] RegPwmStatus        = 6'h08; // 0x020
  localparam logic [5:0] RegPwmDutyActive    = 6'h09; // 0x024
  localparam logic [5:0] RegPwmPeriodActive  = 6'h0A; // 0x028

  localparam logic [5:0] RegQenCtrl          = 6'h10; // 0x040
  localparam logic [5:0] RegQenStatus        = 6'h11; // 0x044
  localparam logic [5:0] RegQenPosition      = 6'h12; // 0x048
  localparam logic [5:0] RegQenVelocity      = 6'h13; // 0x04C
  localparam logic [5:0] RegQenDelta         = 6'h14; // 0x050
  localparam logic [5:0] RegQenIndexPosition = 6'h15; // 0x054
  localparam logic [5:0] RegQenErrorCount    = 6'h16; // 0x058
  localparam logic [5:0] RegQenSamplePeriod  = 6'h17; // 0x05C
  localparam logic [5:0] RegQenSimInput      = 6'h18; // 0x060
  localparam logic [5:0] RegQenDebug         = 6'h19; // 0x064

  // Captured OBI request
  logic req_q;
  logic we_q;
  logic [ObiCfg.AddrWidth-1:0] addr_q;
  logic [ObiCfg.DataWidth-1:0] wdata_q;
  logic [ObiCfg.DataWidth/8-1:0] be_q;
  logic [ObiCfg.IdWidth-1:0] id_q;

  // Software-visible control registers
  logic pinmux_pwm_gpio0_q;
  logic pwm_enable_q;
  logic pwm_polarity_q;
  logic [PwmWidth-1:0] pwm_period_q;
  logic [PwmWidth-1:0] pwm_duty_q;
  logic [1:0] pwm_status_q;

  logic [1:0] pwm_status_d;

  // PWM core signals
  logic pwm_o;
  logic [PwmWidth-1:0] pwm_counter;
  logic [PwmWidth-1:0] pwm_period_active;
  logic [PwmWidth-1:0] pwm_duty_active;
  logic pwm_period_done;
  logic pwm_period_zero;

  // QEN software-visible control registers
  logic qen_enable_q;
  logic qen_index_reset_enable_q;
  logic qen_sim_input_enable_q;
  logic [31:0] qen_sample_period_q;
  logic [2:0] qen_sim_input_q;

  // QEN control pulses
  logic qen_clear_position;
  logic qen_clear_error;

  // QEN input mux
  logic qen_a;
  logic qen_b;
  logic qen_z;

  // QEN core signals
  logic signed [QenWidth-1:0] qen_position;
  logic signed [QenWidth-1:0] qen_velocity;
  logic signed [QenWidth-1:0] qen_delta;
  logic signed [QenWidth-1:0] qen_index_position;
  logic [31:0] qen_error_count;
  logic qen_direction;
  logic qen_index_seen;
  logic qen_invalid_transition;
  logic qen_velocity_valid;
  logic [1:0] qen_ab_state;

  // Read response
  logic [ObiCfg.DataWidth-1:0] rsp_data;
  logic rsp_err;

  // Word offset inside AMCP 4 KiB region.
  logic [5:0] reg_word_offset;
  assign reg_word_offset = addr_q[7:2];

  assign qen_clear_position = req_q && we_q && (reg_word_offset == RegQenCtrl) && wdata_q[1];
  assign qen_clear_error    = req_q && we_q && (reg_word_offset == RegQenCtrl) && wdata_q[2];

  // For the first QEN integration:
  //   sim_input_enable = 1 -> use QEN_SIM_INPUT register bits.
  //   sim_input_enable = 0 -> use GPIO[1]=A, GPIO[2]=B, GPIO[3]=Z.
  assign qen_a = qen_sim_input_enable_q ? qen_sim_input_q[0] : gpio_in_sync_i[1];
  assign qen_b = qen_sim_input_enable_q ? qen_sim_input_q[1] : gpio_in_sync_i[2];
  assign qen_z = qen_sim_input_enable_q ? qen_sim_input_q[2] : gpio_in_sync_i[3];

  // Accept every request immediately.
  assign obi_rsp_o.gnt = obi_req_i.req;

  always_ff @(posedge clk_i or negedge rst_ni) begin
    if (!rst_ni) begin
      req_q   <= 1'b0;
      we_q    <= 1'b0;
      addr_q  <= '0;
      wdata_q <= '0;
      be_q    <= '0;
      id_q    <= '0;
    end else begin
      req_q   <= obi_req_i.req;
      we_q    <= obi_req_i.a.we;
      addr_q  <= obi_req_i.a.addr;
      wdata_q <= obi_req_i.a.wdata;
      be_q    <= obi_req_i.a.be;
      id_q    <= obi_req_i.a.aid;
    end
  end

  // Status flags are sticky and cleared with write-one-to-clear.
  always_comb begin
    pwm_status_d = pwm_status_q;

    if (pwm_period_done) begin
      pwm_status_d[0] = 1'b1;
    end

    if (pwm_period_zero) begin
      pwm_status_d[1] = 1'b1;
    end

    if (req_q && we_q && (reg_word_offset == RegPwmStatus)) begin
      pwm_status_d = pwm_status_d & ~wdata_q[1:0];
    end
  end

  always_ff @(posedge clk_i or negedge rst_ni) begin
    if (!rst_ni) begin
      pinmux_pwm_gpio0_q <= 1'b0;
      pwm_enable_q       <= 1'b0;
      pwm_polarity_q     <= 1'b0;
      pwm_period_q       <= '0;
      pwm_duty_q         <= '0;
      pwm_status_q       <= '0;

      qen_enable_q             <= 1'b0;
      qen_index_reset_enable_q <= 1'b0;
      qen_sim_input_enable_q   <= 1'b1;
      qen_sample_period_q      <= 32'd16;
      qen_sim_input_q          <= 3'b000;
    end else begin
      pwm_status_q <= pwm_status_d;

      if (req_q && we_q) begin
        unique case (reg_word_offset)
          RegAmcpPinmux: begin
            pinmux_pwm_gpio0_q <= wdata_q[0];
          end

          RegPwmCtrl: begin
            pwm_enable_q   <= wdata_q[0];
            pwm_polarity_q <= wdata_q[1];
          end

          RegPwmPeriod: begin
            pwm_period_q <= wdata_q[PwmWidth-1:0];
          end

          RegPwmDuty: begin
            pwm_duty_q <= wdata_q[PwmWidth-1:0];
          end

          RegQenCtrl: begin
            qen_enable_q             <= wdata_q[0];
            qen_index_reset_enable_q <= wdata_q[3];
            qen_sim_input_enable_q   <= wdata_q[4];
          end

          RegQenSamplePeriod: begin
            qen_sample_period_q <= wdata_q[31:0];
          end

          RegQenSimInput: begin
            qen_sim_input_q <= wdata_q[2:0];
          end

          default: begin
            // Read-only or invalid registers are handled by rsp_err.
          end
        endcase
      end
    end
  end

  pwm_core #(
    .Width ( PwmWidth )
  ) i_pwm_core (
    .clk_i,
    .rst_ni,

    .enable_i   ( pwm_enable_q   ),
    .polarity_i ( pwm_polarity_q ),

    .period_cfg_i ( pwm_period_q ),
    .duty_cfg_i   ( pwm_duty_q   ),

    .pwm_o           ( pwm_o             ),
    .counter_o       ( pwm_counter       ),
    .period_active_o ( pwm_period_active ),
    .duty_active_o   ( pwm_duty_active   ),
    .period_done_o   ( pwm_period_done   ),
    .period_zero_o   ( pwm_period_zero   )
  );

  qen_core #(
    .PosWidth    ( QenWidth ),
    .SampleWidth ( 32       )
  ) i_qen_core (
    .clk_i,
    .rst_ni,

    .enable_i             ( qen_enable_q             ),
    .clear_position_i     ( qen_clear_position       ),
    .clear_error_i        ( qen_clear_error          ),
    .index_reset_enable_i ( qen_index_reset_enable_q ),

    .sample_period_i ( qen_sample_period_q ),

    .a_i ( qen_a ),
    .b_i ( qen_b ),
    .z_i ( qen_z ),

    .position_o           ( qen_position           ),
    .velocity_o           ( qen_velocity           ),
    .delta_o              ( qen_delta              ),
    .direction_o          ( qen_direction          ),
    .index_seen_o         ( qen_index_seen         ),
    .index_position_o     ( qen_index_position     ),
    .error_count_o        ( qen_error_count        ),
    .invalid_transition_o ( qen_invalid_transition ),
    .velocity_valid_o     ( qen_velocity_valid     ),
    .ab_state_o           ( qen_ab_state           )
  );

  // GPIO alternate-function routing.
  always_comb begin
    amcp_gpio_o          = '0;
    amcp_gpio_out_en_o   = '0;
    amcp_gpio_override_o = '0;

    amcp_gpio_override_o[0] = pinmux_pwm_gpio0_q;
    amcp_gpio_o[0]          = pwm_o;
    amcp_gpio_out_en_o[0]   = pinmux_pwm_gpio0_q;
  end

  // Read-data and error response generation.
  always_comb begin
    rsp_data = '0;
    rsp_err  = 1'b0;

    if (req_q) begin
      unique case (reg_word_offset)
        RegAmcpId: begin
          rsp_data = AmcpId;
          rsp_err  = we_q;
        end

        RegAmcpVersion: begin
          rsp_data = AmcpVersion;
          rsp_err  = we_q;
        end

        RegAmcpPinmux: begin
          rsp_data = {{(ObiCfg.DataWidth-1){1'b0}}, pinmux_pwm_gpio0_q};
        end

        RegAmcpStatus: begin
          rsp_data = '0;
          rsp_err  = we_q;
        end

        RegPwmCtrl: begin
          rsp_data = {{(ObiCfg.DataWidth-2){1'b0}}, pwm_polarity_q, pwm_enable_q};
        end

        RegPwmPeriod: begin
          rsp_data = {{(ObiCfg.DataWidth-PwmWidth){1'b0}}, pwm_period_q};
        end

        RegPwmDuty: begin
          rsp_data = {{(ObiCfg.DataWidth-PwmWidth){1'b0}}, pwm_duty_q};
        end

        RegPwmCounter: begin
          rsp_data = {{(ObiCfg.DataWidth-PwmWidth){1'b0}}, pwm_counter};
          rsp_err  = we_q;
        end

        RegPwmStatus: begin
          rsp_data = {{(ObiCfg.DataWidth-2){1'b0}}, pwm_status_q};
        end

        RegPwmDutyActive: begin
          rsp_data = {{(ObiCfg.DataWidth-PwmWidth){1'b0}}, pwm_duty_active};
          rsp_err  = we_q;
        end

        RegPwmPeriodActive: begin
          rsp_data = {{(ObiCfg.DataWidth-PwmWidth){1'b0}}, pwm_period_active};
          rsp_err  = we_q;
        end

        RegQenCtrl: begin
          rsp_data = {{(ObiCfg.DataWidth-5){1'b0}},
                      qen_sim_input_enable_q,
                      qen_index_reset_enable_q,
                      2'b00,
                      qen_enable_q};
        end

        RegQenStatus: begin
          rsp_data = {{(ObiCfg.DataWidth-6){1'b0}},
                      qen_velocity_valid,
                      qen_invalid_transition,
                      (qen_error_count != 32'd0),
                      qen_index_seen,
                      qen_direction,
                      qen_enable_q};
          rsp_err  = we_q;
        end

        RegQenPosition: begin
          rsp_data = qen_position;
          rsp_err  = we_q;
        end

        RegQenVelocity: begin
          rsp_data = qen_velocity;
          rsp_err  = we_q;
        end

        RegQenDelta: begin
          rsp_data = qen_delta;
          rsp_err  = we_q;
        end

        RegQenIndexPosition: begin
          rsp_data = qen_index_position;
          rsp_err  = we_q;
        end

        RegQenErrorCount: begin
          rsp_data = qen_error_count;
          rsp_err  = we_q;
        end

        RegQenSamplePeriod: begin
          rsp_data = qen_sample_period_q;
        end

        RegQenSimInput: begin
          rsp_data = {{(ObiCfg.DataWidth-3){1'b0}}, qen_sim_input_q};
        end

        RegQenDebug: begin
          rsp_data = {{(ObiCfg.DataWidth-5){1'b0}}, qen_z, qen_b, qen_a, qen_ab_state};
          rsp_err  = we_q;
        end

        default: begin
          rsp_data = 32'hBADC0DE;
          rsp_err  = 1'b1;
        end
      endcase
    end
  end

  assign obi_rsp_o.rvalid       = req_q;
  assign obi_rsp_o.r.rdata      = rsp_data;
  assign obi_rsp_o.r.rid        = id_q;
  assign obi_rsp_o.r.err        = rsp_err;
  assign obi_rsp_o.r.r_optional = '0;

  // Byte-enable is captured for future partial-write support.
  logic unused_be;
  assign unused_be = ^be_q;

endmodule