// Small read-only user ROM containing a zero-terminated group-name string.
// It occupies the user-domain base address region but only implements a few words.

module user_name_rom #(
  parameter obi_pkg::obi_cfg_t ObiCfg    = obi_pkg::ObiDefaultConfig,
  parameter type               obi_req_t = logic,
  parameter type               obi_rsp_t = logic
) (
  input  logic     clk_i,
  input  logic     rst_ni,
  input  obi_req_t obi_req_i,
  output obi_rsp_t obi_rsp_o
);

  logic req_q;
  logic we_q;
  logic [ObiCfg.AddrWidth-1:0] addr_q;
  logic [ObiCfg.IdWidth-1:0] id_q;

  logic [ObiCfg.DataWidth-1:0] rsp_data;
  logic rsp_err;

  assign obi_rsp_o.gnt = obi_req_i.req;

  always_ff @(posedge clk_i or negedge rst_ni) begin
    if (!rst_ni) begin
      req_q  <= 1'b0;
      we_q   <= 1'b0;
      addr_q <= '0;
      id_q   <= '0;
    end else begin
      req_q  <= obi_req_i.req;
      we_q   <= obi_req_i.a.we;
      addr_q <= obi_req_i.a.addr;
      id_q   <= obi_req_i.a.aid;
    end
  end

  always_comb begin
    rsp_data = '0;
    rsp_err  = 1'b0;

    if (req_q) begin
      if (we_q) begin
        rsp_err = 1'b1;
      end else begin
        unique case (addr_q[6:2])
          // Little-endian packed ASCII:
          // "Rishabh Barola, Chelsea Lai\0"
          5'h00: rsp_data = 32'h68736952; // "Rish"
          5'h01: rsp_data = 32'h20686261; // "abh "
          5'h02: rsp_data = 32'h6f726142; // "Baro"
          5'h03: rsp_data = 32'h202c616c; // "la, "
          5'h04: rsp_data = 32'h6c656843; // "Chel"
          5'h05: rsp_data = 32'h20616573; // "sea "
          5'h06: rsp_data = 32'h0069614c; // "Lai\0"
          default: rsp_data = 32'h00000000;
        endcase
      end
    end
  end

  assign obi_rsp_o.rvalid       = req_q;
  assign obi_rsp_o.r.rdata      = rsp_data;
  assign obi_rsp_o.r.rid        = id_q;
  assign obi_rsp_o.r.err        = rsp_err;
  assign obi_rsp_o.r.r_optional = '0;

endmodule