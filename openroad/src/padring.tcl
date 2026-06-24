# Copyright (c) 2024 ETH Zurich and University of Bologna.
# Licensed under the Apache License, Version 2.0, see LICENSE for details.
# SPDX-License-Identifier: Apache-2.0
#
# Authors:
# - Philippe Sauter <phsauter@iis.ee.ethz.ch>

#
# - The "#pin no.: nn" comment shows the corresponding pin number for the package.

# [QFN48]
#                   package die
#   pins               48    56
#   I/O                40    40
#   Core power          4     4
#   Core ground         -     4
#   Pad  power          4     4
#   Pad  ground         -     4
#
# pad pitch (min)    90.0  90.0
#
# Chip geometry comes from floorplan.tcl
# Keep only the pad positioning/spacing here

# Positioning for every edge works like this:
#   - the IO site spans the entire edge
#   - pads start cornerToPad microns away from the corner (pad -> bond -> gap)
#   - the remaining usable edge length is split into (numPads-1) equal gaps



# 
# bondpad_centroids.csv gives bondpad CENTER coordinates in OpenROAD coordinates.
# With place_bondpad -offset {5.0 -70.0}, the corresponding place_pad
# location is center_coordinate - 40.0 along the pad edge.

make_io_sites -horizontal_site sg13cmos5l_ioSite \
    -vertical_site sg13cmos5l_ioSite \
    -corner_site sg13cmos5l_ioSite \
    -offset $padBond \
    -rotation_horizontal R0 \
    -rotation_vertical R0 \
    -rotation_corner R0

##########################################################################
# Edge: LEFT / WEST                                                       #
##########################################################################

place_pad -row IO_WEST  -location 1586.0 "pad_vddio0"
place_pad -row IO_WEST  -location 1484.0 "pad_uart_rx_i"
place_pad -row IO_WEST  -location 1382.0 "pad_uart_tx_o"
place_pad -row IO_WEST  -location 1280.0 "pad_testmode_i"
place_pad -row IO_WEST  -location 1178.0 "pad_status_o"
place_pad -row IO_WEST  -location 1076.0 "pad_clk_i"
place_pad -row IO_WEST  -location  974.0 "pad_ref_clk_i"
place_pad -row IO_WEST  -location  872.0 "pad_rst_ni"
place_pad -row IO_WEST  -location  770.0 "pad_jtag_tck_i"
place_pad -row IO_WEST  -location  668.0 "pad_jtag_trst_ni"
place_pad -row IO_WEST  -location  566.0 "pad_jtag_tms_i"
place_pad -row IO_WEST  -location  464.0 "pad_jtag_tdi_i"
place_pad -row IO_WEST  -location  362.0 "pad_jtag_tdo_o"
place_pad -row IO_WEST  -location  260.0 "pad_vdd0"

##########################################################################
# Edge: BOTTOM / SOUTH                                                    #
##########################################################################

place_pad -row IO_SOUTH -location  250.0 "pad_vss0"
place_pad -row IO_SOUTH -location  358.0 "pad_vssio1"
place_pad -row IO_SOUTH -location  466.0 "pad_vddio1"
place_pad -row IO_SOUTH -location  574.0 "pad_gpio0_io"
place_pad -row IO_SOUTH -location  682.0 "pad_gpio1_io"
place_pad -row IO_SOUTH -location  790.0 "pad_gpio2_io"
place_pad -row IO_SOUTH -location  898.0 "pad_gpio3_io"
place_pad -row IO_SOUTH -location 1006.0 "pad_gpio4_io"
place_pad -row IO_SOUTH -location 1114.0 "pad_gpio5_io"
place_pad -row IO_SOUTH -location 1222.0 "pad_gpio6_io"
place_pad -row IO_SOUTH -location 1330.0 "pad_gpio7_io"
place_pad -row IO_SOUTH -location 1438.0 "pad_gpio8_io"
place_pad -row IO_SOUTH -location 1546.0 "pad_gpio9_io"
place_pad -row IO_SOUTH -location 1654.0 "pad_gpio10_io"
place_pad -row IO_SOUTH -location 1762.0 "pad_gpio11_io"
place_pad -row IO_SOUTH -location 1870.0 "pad_vdd1"
place_pad -row IO_SOUTH -location 1978.0 "pad_vss1"
place_pad -row IO_SOUTH -location 2086.0 "pad_vssio2"

##########################################################################
# Edge: RIGHT / EAST                                                      #
##########################################################################

place_pad -row IO_EAST  -location  250.0 "pad_vddio2"
place_pad -row IO_EAST  -location  352.0 "pad_gpio12_io"
place_pad -row IO_EAST  -location  454.0 "pad_gpio13_io"
place_pad -row IO_EAST  -location  556.0 "pad_gpio14_io"
place_pad -row IO_EAST  -location  658.0 "pad_gpio15_io"
place_pad -row IO_EAST  -location  760.0 "pad_gpio16_io"
place_pad -row IO_EAST  -location  862.0 "pad_gpio17_io"
place_pad -row IO_EAST  -location  964.0 "pad_gpio18_io"
place_pad -row IO_EAST  -location 1066.0 "pad_gpio19_io"
place_pad -row IO_EAST  -location 1168.0 "pad_gpio20_io"
place_pad -row IO_EAST  -location 1270.0 "pad_gpio21_io"
place_pad -row IO_EAST  -location 1372.0 "pad_gpio22_io"
place_pad -row IO_EAST  -location 1474.0 "pad_gpio23_io"
place_pad -row IO_EAST  -location 1576.0 "pad_vdd2"

##########################################################################
# Edge: TOP / NORTH                                                       #
##########################################################################

place_pad -row IO_NORTH -location 2086.0 "pad_vss2"
place_pad -row IO_NORTH -location 1978.0 "pad_vssio3"
place_pad -row IO_NORTH -location 1870.0 "pad_vddio3"
place_pad -row IO_NORTH -location 1762.0 "pad_gpio24_io"
place_pad -row IO_NORTH -location 1654.0 "pad_gpio25_io"
place_pad -row IO_NORTH -location 1546.0 "pad_gpio26_io"
place_pad -row IO_NORTH -location 1438.0 "pad_gpio27_io"
place_pad -row IO_NORTH -location 1330.0 "pad_gpio28_io"
place_pad -row IO_NORTH -location 1222.0 "pad_gpio29_io"
place_pad -row IO_NORTH -location 1114.0 "pad_gpio30_io"
place_pad -row IO_NORTH -location 1006.0 "pad_gpio31_io"
place_pad -row IO_NORTH -location  898.0 "pad_unused0_o"
place_pad -row IO_NORTH -location  790.0 "pad_unused1_o"
place_pad -row IO_NORTH -location  682.0 "pad_unused2_o"
place_pad -row IO_NORTH -location  574.0 "pad_unused3_o"
place_pad -row IO_NORTH -location  466.0 "pad_vdd3"
place_pad -row IO_NORTH -location  358.0 "pad_vss3"
place_pad -row IO_NORTH -location  250.0 "pad_vssio0"
# Fill in the rest of the padring
place_corners $iocorner

place_io_fill -row IO_NORTH {*}$iofill
place_io_fill -row IO_SOUTH {*}$iofill
place_io_fill -row IO_WEST  {*}$iofill
place_io_fill -row IO_EAST  {*}$iofill

# Connect built-in power rings
connect_by_abutment

# Bondpad integrated into IO cell (or bondpad after OpenROAD):
# tells OpenROAD which IO-Cell pin is the pad and places the IO-terminal
# (the internal concept of an IO) ontop of this pin
# place_io_terminals */pad

# Bondpad as separate cell placed in OpenROAD:
# place the bonding pad relative to the IO cell
place_bondpad -bond $bondPadCell -offset {5.0 -70.0} pad_*

# remove rows created by via make_io_sites as they are no longer needed
remove_io_rows
