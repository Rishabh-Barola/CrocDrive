source scripts/init_tech.tcl

read_def out/croc.def
read_sdc out/croc.sdc

puts "================ VDD IR DROP ================"
set_pdnsim_net_voltage -net VDD -voltage 1.2
analyze_power_grid \
  -vsrc src/Vsrc_croc_vdd.loc \
  -net VDD \
  -corner tt \
  -error_file reports/vdd_connectivity_errors.rpt

puts "================ VSS GROUND BOUNCE ================"
set_pdnsim_net_voltage -net VSS -voltage 0.0
analyze_power_grid \
  -vsrc src/Vsrc_croc_vss.loc \
  -net VSS \
  -corner tt \
  -error_file reports/vss_connectivity_errors.rpt

exit
