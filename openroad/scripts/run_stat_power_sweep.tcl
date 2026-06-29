source scripts/init_tech.tcl

read_verilog out/croc.v
link_design croc_chip
read_sdc out/croc.sdc
read_spef out/croc.spef

foreach act {0.01 0.05 0.10} {
  puts "================================================================"
  puts "Statistical power, TT corner, global activity = $act"
  puts "================================================================"
  set_power_activity -global -activity $act
  set_power_activity -input_port rst_ni -activity 0
  report_power -corner tt

  puts "================================================================"
  puts "Statistical power, FF corner, global activity = $act"
  puts "================================================================"
  report_power -corner ff
}

exit
