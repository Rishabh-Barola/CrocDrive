// Copyright 2024 ETH Zurich and University of Bologna.
// Solderpad Hardware License, Version 0.51, see LICENSE for details.
// SPDX-License-Identifier: SHL-0.51
//
// Authors:
// - Philippe Sauter <phsauter@iis.ee.ethz.ch>

`include "obi/typedef.svh"

package user_pkg;

  //////////////////
  // User Manager //
  //////////////////

  // None


  ///////////////////////
  // User Subordinates //
  ///////////////////////

  // The base address of the user domain can be retrieved from `croc_pkg::UserBaseAddr`.
  // Subordinates are placed at 4 KiB boundaries.
  localparam bit [31:0] UserRomBaseAddr  = croc_pkg::UserBaseAddr + 32'h0000_0000;
  localparam bit [31:0] UserAmcpBaseAddr = croc_pkg::UserBaseAddr + 32'h0000_1000;

  /// Enum with user domain demultiplexer subordinate idxs
  typedef enum bit [4:0] {
    UserError = 0,
    UserRom   = 1,
    UserAmcp  = 2
  } user_demux_outputs_e;

  /// Address rules given to user domain demultiplexer
  localparam croc_pkg::addr_map_rule_t [1:0] UserAddrMap = '{
    '{
      idx:        UserRom,
      start_addr: UserRomBaseAddr,
      end_addr:   UserRomBaseAddr + 32'h0000_1000
    },
    '{
      idx:        UserAmcp,
      start_addr: UserAmcpBaseAddr,
      end_addr:   UserAmcpBaseAddr + 32'h0000_1000
    }
  };

  // All addresses outside the defined address rules go to the error subordinate.
  localparam int unsigned NumDemuxSbr = $size(UserAddrMap) + 1;

endpackage

