# Copyright 2023 ETH Zurich and University of Bologna.
# Solderpad Hardware License, Version 0.51, see LICENSE for details.
# SPDX-License-Identifier: SHL-0.51

# Authors:
# - Tobias Senti      <tsenti@ethz.ch>
# - Jannis Schönleber <janniss@iis.ee.ethz.ch>
# - Philippe Sauter   <phsauter@iis.ee.ethz.ch>

# Stage 02: Placement (Repair Netlist + Global Placement + Detailed Placement)
#
# This stage performs:
# - Initial repair of the netlist (tie cells, buffers)
# - Global placement (2-pass: rough + routability-driven)
# - Detailed placement (legalization)
#
# Required environment variables:
#   PROJ_NAME    - Project name (e.g., "croc")
#   TOP_DESIGN   - Top module name
#
# Input checkpoint: 01_${PROJ_NAME}.floorplan
# Output checkpoint: 02_${PROJ_NAME}.placed

###############################################################################
# Setup
###############################################################################
source scripts/startup.tcl

# Load checkpoint from previous stage
load_checkpoint 01_${proj_name}.floorplan

# Set layers used for estimate_parasitics
setDefaultParasitics
set_dont_use $dont_use_cells

# Add one-site spacing between standard cells.
# This avoids full-GDS M1 pin/notch/short issues not visible in LEF.
set_placement_padding -global -left 1 -right 1


utl::report "###############################################################################"
utl::report "# Stage 02: PLACEMENT"
utl::report "###############################################################################"

utl::report "###############################################################################"
utl::report "# 02-01: Initial Repair Netlist"
utl::report "###############################################################################"

# Don't touch clock-tree related nets as repair_timing can insert buffers
# which then prevents CTS from running
# Protect clock-tree related nets before CTS.
# In the mapped EZ130 standard-cell library, sequential clock pins are CK.

set clock_nets [get_nets -of_objects [get_pins -of_objects "*_reg" -filter "name == CK"]]
set_dont_touch $clock_nets

utl::report "Repair tie fanout"
repair_tie_fanout $tieHiPin 
repair_tie_fanout $tieLoPin 

utl::report "Remove buffers"
remove_buffers

utl::report "Repair design"
repair_design -verbose

save_checkpoint 02-01_${proj_name}.pre_place


utl::report "###############################################################################"
utl::report "# 02-02: Global Placement"
utl::report "###############################################################################"

set_thread_count 8

# global_placement parameters:
# density:            In every part of the chip, about N% of the area is occupied by standard cells
# routability_driven: Reduce density target when there are a lot of wires in an area
# check_overflow:     Higher means routability starts being considered earlier in placement
#                     too early -> very dense regions, too late -> little to no effect
# timing_driven:      Prioritize near-critical timing paths (reduce their length)

# Rough placement to get parasitics from steiner-tree estimate so we can run repair_timing
utl::report "Global Placement (1)"
global_placement -density 0.60
report_metrics "02-02_${proj_name}.gpl1"
report_image "02-02_${proj_name}.gpl1" true true
save_checkpoint 02-02_${proj_name}.gpl1

utl::report "Estimate parasitics"
estimate_parasitics -placement
utl::report "Repair design"
repair_design -verbose 
save_checkpoint 02-02_${proj_name}.gpl1_fix

repair_tie_fanout $tieHiPin
repair_tie_fanout $tieLoPin


utl::report "Repair setup"
repair_timing -setup -verbose
save_checkpoint 02-02_${proj_name}.gpl1_repaired

# Actual global placement with routability and timing driven
utl::report "Global Placement (2)"
global_placement -density 0.60 \
                 -routability_driven \
                 -routability_check_overflow 0.30 \
                 -timing_driven
report_metrics "02-02_${proj_name}.gpl2"
report_image "02-02_${proj_name}.gpl2" true true
save_checkpoint 02-02_${proj_name}.gpl2

# These two NOR4 drivers were identified in the GUI/OpenDB dump as driving
# high-fanout internal nets with many max-slew violations. Automatic
# repair_design did not resize them, so we upsize them explicitly.
replace_cell {i_croc_soc/i_croc/_3764_} NOR4X2
replace_cell {i_croc_soc/i_croc/_3642_} NOR4X2

utl::report "Estimate parasitics after Global Placement (2)"
estimate_parasitics -placement

utl::report "Report DRV after GPL2 before final repair"
report_check_types -max_slew -max_cap -max_fanout -violators > ${report_dir}/02_drv_after_gpl2_before_repair.rpt
puts "DRV after GPL2 before repair: max_slew=[sta::max_slew_violation_count] max_fanout=[sta::max_fanout_violation_count] max_cap=[sta::max_capacitance_violation_count]"

utl::report "Final placement-stage DRV repair"
repair_design -verbose

utl::report "Final placement-stage setup repair"
repair_timing -setup -skip_pin_swap -verbose -repair_tns 100
utl::report "Targeted upsize of high-fanout internal decode/control drivers"



save_checkpoint 02-02_${proj_name}.gpl2_targeted_upsize


utl::report "Report DRV after final placement repair"
report_check_types -max_slew -max_cap -max_fanout -violators > ${report_dir}/02_drv_after_final_repair.rpt
puts "DRV after final repair: max_slew=[sta::max_slew_violation_count] max_fanout=[sta::max_fanout_violation_count] max_cap=[sta::max_capacitance_violation_count]"

save_checkpoint 02-02_${proj_name}.gpl2_repaired


utl::report "###############################################################################"
utl::report "# 02-03: Detailed Placement"
utl::report "###############################################################################"

# Legalize overlapping cells
utl::report "Detailed placement"
detailed_placement

utl::report "Optimize mirroring"
optimize_mirroring

utl::report "Check placement"
check_placement -verbose

utl::report "Estimate parasitics"
estimate_parasitics -placement

report_metrics "02_${proj_name}.placed"
save_checkpoint 02_${proj_name}.placed
report_image "02_${proj_name}.placed" true true

utl::report "###############################################################################"
utl::report "# Stage 02 complete: Checkpoint saved to ${save_dir}/02_${proj_name}.placed.zip"
utl::report "###############################################################################"
