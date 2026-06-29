source scripts/init_tech.tcl

read_def out/croc.def
read_sdc out/croc.sdc

set_pdnsim_net_voltage -net VSS -voltage 0.0

analyze_power_grid \
  -vsrc src/Vsrc_croc_vss.loc \
  -net VSS \
  -corner tt \
  -error_file reports/vss_connectivity_errors.rpt

gui::set_display_controls "Heat Maps/IR Drop" visible true
gui::set_heatmap IRDrop Layer Metal1
gui::set_heatmap IRDrop ShowLegend 1
gui::zoom_fit
