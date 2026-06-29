# Copyright 2023 ETH Zurich and University of Bologna.
# Solderpad Hardware License, Version 0.51, see LICENSE for details.
# SPDX-License-Identifier: SHL-0.51

# Stage 03: Clock Tree Synthesis (CTS)

source scripts/startup.tcl

load_checkpoint 02_${proj_name}.placed

setDefaultParasitics
set_dont_use $dont_use_cells

utl::report "###############################################################################"
utl::report "# Stage 03: CLOCK TREE SYNTHESIS"
utl::report "###############################################################################"

# EZ130 mapped sequential cells use CK, not CLK.
set clock_nets [get_nets -of_objects [get_pins -of_objects "*_reg" -filter "name == CK"]]
unset_dont_touch $clock_nets

utl::report "Repair clock inverters"
repair_clock_inverters

utl::report "Estimate parasitics before CTS"
estimate_parasitics -placement

utl::report "Clock Tree Synthesis"

set_wire_rc -clock -layer Metal4
set_wire_rc -signal -layer Metal3

configure_cts_characterization -max_cap 2.0

report_check_types -max_slew -max_cap -max_fanout -violators > ${report_dir}/03_drv_before_cts.rpt
puts "DRV before CTS: max_slew=[sta::max_slew_violation_count] max_fanout=[sta::max_fanout_violation_count] max_cap=[sta::max_capacitance_violation_count]"

clock_tree_synthesis \
  -buf_list $ctsBuf \
  -root_buf $ctsBufRoot \
  -sink_clustering_enable \
  -sink_clustering_size 10 \
  -sink_clustering_levels 3 \
  -clustering_unbalance_ratio 0.25 \
  -sink_clustering_max_diameter 100 \
  -obstruction_aware \
  -balance_levels \
  -repair_clock_nets

report_check_types -max_slew -max_cap -max_fanout -violators > ${report_dir}/03_drv_after_cts_before_repair.rpt
puts "DRV after CTS before repair: max_slew=[sta::max_slew_violation_count] max_fanout=[sta::max_fanout_violation_count] max_cap=[sta::max_capacitance_violation_count]"

utl::report "Detailed placement after CTS"
set DPL_ARGS {}
detailed_placement {*}$DPL_ARGS

utl::report "Estimate parasitics after CTS"
estimate_parasitics -placement

set_propagated_clock [all_clocks]

report_metrics "03_${proj_name}.cts_unrepaired"


# Do not run repair_design here; routing stage already has repair_design with global-route parasitics.

utl::report "Repair setup after CTS"
repair_timing -setup -setup_margin 0.1 -skip_pin_swap -verbose -repair_tns 100

utl::report "Detailed placement after CTS setup repair"
detailed_placement {*}$DPL_ARGS

utl::report "Check placement"
check_placement -verbose

utl::report "Estimate parasitics final CTS"
estimate_parasitics -placement


report_cts -out_file ${report_dir}/03_${proj_name}.cts.rpt
report_clock_latency -clock clk_sys > ${report_dir}/03_${proj_name}.clock_latency.rpt
report_check_types -max_slew -max_cap -max_fanout -violators > ${report_dir}/03_drv_final_cts.rpt
puts "DRV final CTS: max_slew=[sta::max_slew_violation_count] max_fanout=[sta::max_fanout_violation_count] max_cap=[sta::max_capacitance_violation_count]"

report_metrics "03_${proj_name}.cts"
save_checkpoint 03_${proj_name}.cts
report_image "03_${proj_name}.cts" true false true

utl::report "###############################################################################"
utl::report "# Stage 03 complete: Checkpoint saved to ${save_dir}/03_${proj_name}.cts.zip"
utl::report "###############################################################################"
