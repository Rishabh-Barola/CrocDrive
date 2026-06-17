// Copyright 2024 ETH Zurich and University of Bologna.
// Solderpad Hardware License, Version 0.51, see LICENSE for details.
// SPDX-License-Identifier: SHL-0.51
//
// Authors:
// - Philippe Sauter <phsauter@iis.ee.ethz.ch>

module user_domain import user_pkg::*; import croc_pkg::*; #(
  parameter int unsigned GpioCount = 16,
  parameter int unsigned NumExternalIrqs = 4
) (
  input  logic      clk_i,
  input  logic      ref_clk_i,
  input  logic      rst_ni,
  input  logic      testmode_i,

  input  sbr_obi_req_t user_sbr_obi_req_i, // User Sbr (rsp_o), Croc Mgr (req_i)
  output sbr_obi_rsp_t user_sbr_obi_rsp_o,

  output mgr_obi_req_t user_mgr_obi_req_o, // User Mgr (req_o), Croc Sbr (rsp_i)
  input  mgr_obi_rsp_t user_mgr_obi_rsp_i,

  input  logic [GpioCount-1:0] gpio_in_sync_i,

  output logic [GpioCount-1:0] amcp_gpio_o,
  output logic [GpioCount-1:0] amcp_gpio_out_en_o,
  output logic [GpioCount-1:0] amcp_gpio_override_o,

  output logic [NumExternalIrqs-1:0] interrupts_o
);

  assign interrupts_o = '0;

  //////////////////////
  // User Manager MUX //
  //////////////////////

  // No user-domain manager in this project stage.
  assign user_mgr_obi_req_o = '0;

  // ref_clk_i and user_mgr_obi_rsp_i are unused for the PWM-only design.
  logic unused_ref_clk;
  assign unused_ref_clk = ref_clk_i;


  ////////////////////////////
  // User Subordinate DEMUX //
  ////////////////////////////

  sbr_obi_req_t [NumDemuxSbr-1:0] all_user_sbr_obi_req;
  sbr_obi_rsp_t [NumDemuxSbr-1:0] all_user_sbr_obi_rsp;

  // Error subordinate bus
  sbr_obi_req_t user_error_obi_req;
  sbr_obi_rsp_t user_error_obi_rsp;

  // User ROM bus
  sbr_obi_req_t user_rom_obi_req;
  sbr_obi_rsp_t user_rom_obi_rsp;

  // AMCP bus
  sbr_obi_req_t user_amcp_obi_req;
  sbr_obi_rsp_t user_amcp_obi_rsp;

  // Fanout into readable signals
  assign user_error_obi_req              = all_user_sbr_obi_req[UserError];
  assign all_user_sbr_obi_rsp[UserError] = user_error_obi_rsp;

  assign user_rom_obi_req              = all_user_sbr_obi_req[UserRom];
  assign all_user_sbr_obi_rsp[UserRom] = user_rom_obi_rsp;

  assign user_amcp_obi_req              = all_user_sbr_obi_req[UserAmcp];
  assign all_user_sbr_obi_rsp[UserAmcp] = user_amcp_obi_rsp;


  //-----------------------------------------------------------------------------------------------
  // Demultiplex to User Subordinates according to address map
  //-----------------------------------------------------------------------------------------------

  logic [cf_math_pkg::idx_width(NumDemuxSbr)-1:0] user_idx;

  addr_decode #(
    .NoIndices ( NumDemuxSbr                    ),
    .NoRules   ( $size(UserAddrMap)             ),
    .addr_t    ( logic[SbrObiCfg.DataWidth-1:0] ),
    .rule_t    ( addr_map_rule_t                ),
    .Napot     ( 1'b0                           )
  ) i_addr_decode_periphs (
    .addr_i           ( user_sbr_obi_req_i.a.addr ),
    .addr_map_i       ( UserAddrMap               ),
    .idx_o            ( user_idx                  ),
    .dec_valid_o      (),
    .dec_error_o      (),
    .en_default_idx_i ( 1'b1      ),
    .default_idx_i    ( UserError )
  );

  obi_demux #(
    .ObiCfg      ( SbrObiCfg     ),
    .obi_req_t   ( sbr_obi_req_t ),
    .obi_rsp_t   ( sbr_obi_rsp_t ),
    .NumMgrPorts ( NumDemuxSbr   ),
    .NumMaxTrans ( 2             )
  ) i_obi_demux (
    .clk_i,
    .rst_ni,

    .sbr_port_select_i ( user_idx             ),
    .sbr_port_req_i    ( user_sbr_obi_req_i   ),
    .sbr_port_rsp_o    ( user_sbr_obi_rsp_o   ),

    .mgr_ports_req_o   ( all_user_sbr_obi_req ),
    .mgr_ports_rsp_i   ( all_user_sbr_obi_rsp )
  );


  //-------------------------------------------------------------------------------------------------
  // User Subordinates
  //-------------------------------------------------------------------------------------------------

  user_name_rom #(
    .ObiCfg    ( SbrObiCfg     ),
    .obi_req_t ( sbr_obi_req_t ),
    .obi_rsp_t ( sbr_obi_rsp_t )
  ) i_user_name_rom (
    .clk_i,
    .rst_ni,

    .obi_req_i ( user_rom_obi_req ),
    .obi_rsp_o ( user_rom_obi_rsp )
  );

  user_amcp #(
    .GpioCount ( GpioCount     ),
    .PwmWidth  ( 16            ),
    .ObiCfg    ( SbrObiCfg     ),
    .obi_req_t ( sbr_obi_req_t ),
    .obi_rsp_t ( sbr_obi_rsp_t )
  ) i_user_amcp (
    .clk_i,
    .rst_ni,

    .obi_req_i ( user_amcp_obi_req ),
    .obi_rsp_o ( user_amcp_obi_rsp ),

    .gpio_in_sync_i       ( gpio_in_sync_i       ),
    .amcp_gpio_o          ( amcp_gpio_o          ),
    .amcp_gpio_out_en_o   ( amcp_gpio_out_en_o   ),
    .amcp_gpio_override_o ( amcp_gpio_override_o )
  );

  obi_err_sbr #(
    .ObiCfg      ( SbrObiCfg     ),
    .obi_req_t   ( sbr_obi_req_t ),
    .obi_rsp_t   ( sbr_obi_rsp_t ),
    .NumMaxTrans ( 1             ),
    .RspData     ( 32'hBADCAB1E  )
  ) i_user_err (
    .clk_i,
    .rst_ni,
    .testmode_i ( testmode_i         ),
    .obi_req_i  ( user_error_obi_req ),
    .obi_rsp_o  ( user_error_obi_rsp )
  );

endmodule