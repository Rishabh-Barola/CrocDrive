# # Copyright 2023 ETH Zurich and University of Bologna.
# # Solderpad Hardware License, Version 0.51, see LICENSE for details.
# # SPDX-License-Identifier: SHL-0.51

# # Authors:
# # - Tobias Senti      <tsenti@ethz.ch>
# # - Jannis Schönleber <janniss@iis.ee.ethz.ch>
# # - Philippe Sauter   <phsauter@iis.ee.ethz.ch>

# # Stage 04: Routing (Global Route + Detailed Route)
# #
# # This stage performs:
# # - Global routing with congestion awareness
# # - Incremental repair and re-routing
# # - Antenna repair
# # - Detailed routing
# #
# # Required environment variables:
# #   PROJ_NAME    - Project name (e.g., "croc")
# #   TOP_DESIGN   - Top module name
# #
# # Input checkpoint: 03_${PROJ_NAME}.cts
# # Output checkpoint: 04_${PROJ_NAME}.routed

# ###############################################################################
# # Setup
# ###############################################################################
# source scripts/startup.tcl

# # Load checkpoint from previous stage
# load_checkpoint 03_${proj_name}.cts

# # Set layers used for estimate_parasitics
# setDefaultParasitics
# set_dont_use $dont_use_cells


# utl::report "###############################################################################"
# utl::report "# Stage 04: ROUTING"
# utl::report "###############################################################################"

# utl::report "###############################################################################"
# utl::report "# 04-01: Global Route"
# utl::report "###############################################################################"

# # Reduce TM1 to avoid too much routing there (bigger tracks -> bad for routing)
# set_global_routing_layer_adjustment TopMetal1 0.20
# set_routing_layers -signal Metal2-TopMetal1 -clock Metal2-TopMetal1

# utl::report "Global route"
# global_route -guide_file ${report_dir}/04_${proj_name}_route.guide \
#     -congestion_report_file ${report_dir}/04_${proj_name}_route_congestion.rpt \
#     -allow_congestion
# # Default params but -allow_congestion
# # It continues even if it didn't find a solution (may be able to fix afterwards)

# utl::report "Estimate parasitics"
# estimate_parasitics -global_routing
# report_metrics "04-01_${proj_name}.grt"
# save_checkpoint 04-01_${proj_name}.grt
# report_image "04-01_${proj_name}.grt" true false false true

# grt::set_verbose 0

# utl::report "Perform conservative DRV repair..."
# repair_design -slew_margin 10 -cap_margin 10 -verbose


# utl::report "Repair setup and hold violations..."
# repair_timing -setup -setup_margin 0.10 -verbose -repair_tns 100
# repair_timing -hold  -hold_margin 0.05  -verbose -repair_tns 100


# utl::report "GRT incremental..."
# # Run to get modified net by DPL
# global_route -start_incremental -allow_congestion

# # Running DPL to fix overlapped instances
# detailed_placement

# # Route only the modified net by DPL
# global_route -end_incremental \
#             -guide_file ${report_dir}/04_${proj_name}_route.guide \
#             -congestion_report_file ${report_dir}/04_${proj_name}_route_congestion.rpt \
#             -allow_congestion \
#             -verbose

# estimate_parasitics -global_routing
# report_metrics "04-01_${proj_name}.grt_repaired"
# save_checkpoint 04-01_${proj_name}.grt_repaired
# report_image "04-01_${proj_name}.grt_repaired" true true false true


# utl::report "###############################################################################"
# utl::report "# 04-02: Detailed Route"
# utl::report "###############################################################################"

# # Repair antennas (requires LEF cell with class 'CORE ANTENNACELL')
# # ratio_margin: 30% safety margin on antenna ratios
# repair_antennas -ratio_margin 30 -iterations 5

# utl::report "Detailed route"
# set_thread_count 8
# detailed_route -output_drc ${report_dir}/04_${proj_name}_route_drc.rpt \
#                -drc_report_iter_step 5 \
#                -save_guide_updates \
#                -clean_patches \
#                -droute_end_iter 20 \
#                -verbose 1

# utl::report "Saving detailed route"
# save_checkpoint 04_${proj_name}.routed
# report_metrics "04_${proj_name}.routed"
# report_image "04_${proj_name}.routed" true false false true

# utl::report "###############################################################################"
# utl::report "# Stage 04 complete: Checkpoint saved to ${save_dir}/04_${proj_name}.routed.zip"
# utl::report "###############################################################################"
# Copyright 2023 ETH Zurich and University of Bologna.

# Solderpad Hardware License, Version 0.51, see LICENSE for details.

# SPDX-License-Identifier: SHL-0.51

# Authors:

# - Tobias Senti      [tsenti@ethz.ch](mailto:tsenti@ethz.ch)

# - Jannis Schönleber [janniss@iis.ee.ethz.ch](mailto:janniss@iis.ee.ethz.ch)

# - Philippe Sauter   [phsauter@iis.ee.ethz.ch](mailto:phsauter@iis.ee.ethz.ch)

# Stage 04: Routing (Global Route + Detailed Route)

#

# This stage performs:

# - Global routing with congestion awareness

# - Conservative DRV repair

# - Setup/hold repair

# - Incremental legalization and rerouting

# - Antenna repair

# - Detailed routing

#

# Required environment variables:

# PROJ_NAME    - Project name (e.g., "croc")

# TOP_DESIGN   - Top module name

#

# Input checkpoint: 03_${PROJ_NAME}.cts

# Output checkpoint: 04_${PROJ_NAME}.routed

###############################################################################

# Setup

###############################################################################
source scripts/startup.tcl

# Load checkpoint from previous stage

load_checkpoint 03_${proj_name}.cts

# Set layers used for estimate_parasitics

setDefaultParasitics
set_dont_use $dont_use_cells

utl::report "###############################################################################"
utl::report "# Stage 04: ROUTING"
utl::report "###############################################################################"

utl::report "###############################################################################"
utl::report "# 04-01: Global Route"
utl::report "###############################################################################"

# Reduce TM1 usage. TopMetal1 has coarse tracks and is also important for PDN.

set_global_routing_layer_adjustment Metal2-Metal3 0.30
set_global_routing_layer_adjustment TopMetal1 0.20
set_routing_layers -signal Metal2-TopMetal1 -clock Metal2-TopMetal1

utl::report "Global route"
global_route -guide_file ${report_dir}/04_${proj_name}_route.guide -congestion_report_file ${report_dir}/04_${proj_name}_route_congestion.rpt -allow_congestion

utl::report "Estimate parasitics"
estimate_parasitics -global_routing

utl::report "Report initial global-route metrics"
report_metrics "04-01_${proj_name}.grt"
save_checkpoint 04-01_${proj_name}.grt
report_image "04-01_${proj_name}.grt" true false false true

grt::set_verbose 0

utl::report "Report DRV before repair"
report_check_types -max_slew -max_cap -max_fanout -violators > ${report_dir}/04_drv_before_repair.rpt

# Conservative DRV repair.

# Do not use aggressive two-pass repair or -max_wire_length here.

utl::report "Perform conservative DRV repair"
repair_design -slew_margin 10 -cap_margin 10 -verbose

utl::report "Report DRV after repair_design"
report_check_types -max_slew -max_cap -max_fanout -violators > ${report_dir}/04_drv_after_repair_design.rpt

# Repair setup and hold with margins.

# Keep hold margin modest to avoid unnecessary buffer insertion.

utl::report "Repair setup and hold violations"
repair_timing -skip_pin_swap -setup -verbose -repair_tns 100
repair_timing -skip_pin_swap -hold -hold_margin 0.1 -verbose -repair_tns 100

utl::report "Report DRV after timing repair"
report_check_types -max_slew -max_cap -max_fanout -violators > ${report_dir}/04_drv_after_timing_repair.rpt

utl::report "GRT incremental"
global_route -start_incremental -allow_congestion

# Legalize cells inserted/resized by repair_design and repair_timing.

detailed_placement

utl::report "Check placement after legalization"
check_placement -verbose

# Reroute only modified nets.

global_route -end_incremental -guide_file ${report_dir}/04_${proj_name}_route.guide -congestion_report_file ${report_dir}/04_${proj_name}_route_congestion.rpt -allow_congestion -verbose

utl::report "Estimate parasitics after repaired global route"
estimate_parasitics -global_routing

utl::report "Report repaired global-route metrics"
report_metrics "04-01_${proj_name}.grt_repaired"
save_checkpoint 04-01_${proj_name}.grt_repaired
report_image "04-01_${proj_name}.grt_repaired" true true false true

utl::report "Report DRV after repaired global route"
report_check_types -max_slew -max_cap -max_fanout -violators > ${report_dir}/04_drv_after_grt_repaired.rpt

utl::report "###############################################################################"
utl::report "# 04-02: Detailed Route"
utl::report "###############################################################################"

# Repair antennas before detailed routing.

repair_antennas -ratio_margin 30 -iterations 5

utl::report "Detailed route"
set_thread_count 8
detailed_route -output_drc ${report_dir}/04_${proj_name}_route_drc.rpt -droute_end_iter 30 -drc_report_iter_step 5 -save_guide_updates -clean_patches -verbose 1

utl::report "Saving detailed route"
save_checkpoint 04_${proj_name}.routed

utl::report "Report final routed metrics"
report_metrics "04_${proj_name}.routed"
report_check_types -max_slew -max_cap -max_fanout -violators > ${report_dir}/04_drv_routed_violators.rpt

report_image "04_${proj_name}.routed" true false false true

utl::report "###############################################################################"
utl::report "# Stage 04 complete: Checkpoint saved to ${save_dir}/04_${proj_name}.routed.zip"
utl::report "###############################################################################"
