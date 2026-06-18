# #!/usr/bin/env bash
# set -euo pipefail

# ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# run_in() {
#   local dir="$1"
#   shift
#   echo
#   echo "### [$dir] $*"
#   (cd "$ROOT_DIR/$dir" && "$@")
# }

# echo "### AMCP frontend regression"

# echo "### Software build"
# rm -rf "$ROOT_DIR/sw/bin" "$ROOT_DIR/sw/build"
# run_in sw oseda make

# echo "### Standalone PWM core file-based test"
# run_in rtl/user_domain/tb/pwm_core_file_tb python3 gen_stimuli.py
# run_in rtl/user_domain/tb/pwm_core_file_tb python3 gen_exp_response.py
# rm -rf "$ROOT_DIR/rtl/user_domain/tb/pwm_core_file_tb/obj_dir"
# run_in rtl/user_domain/tb/pwm_core_file_tb oseda verilator \
#   --binary \
#   --timing \
#   -Wno-fatal \
#   --trace-fst \
#   --trace-structs \
#   --top tb_pwm_core_file \
#   ../../pwm_core.sv \
#   tb_pwm_core_file.sv
# run_in rtl/user_domain/tb/pwm_core_file_tb ./obj_dir/Vtb_pwm_core_file

# echo "### Croc Verilator simulation"
# run_in verilator oseda ./run_verilator.sh --flist
# rm -rf "$ROOT_DIR/verilator/obj_dir"
# run_in verilator oseda ./run_verilator.sh --build --run ../sw/bin/test/test_pwm.hex

# echo
# echo "### AMCP frontend regression PASSED"


#!/usr/bin/env bash

set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

run_in() {
  local dir="$1"
  shift
  (cd "$ROOT_DIR/$dir" && "$@")
}

echo "### Setup (IHP13)"
git submodule update --init --recursive
icdesign ihp13 -update all -nogui

echo "### Software"
run_in sw oseda make

echo "### Simulation (Verilator)"
run_in verilator oseda ./run_verilator.sh --flist
run_in verilator oseda ./run_verilator.sh --build --run ../sw/bin/helloworld.hex
run_in verilator oseda ./run_verilator.sh --build --run ../sw/bin/test/print_config.hex
run_in verilator oseda ./run_verilator.sh --build --run ../sw/bin/test/test_clint.hex
run_in verilator oseda ./run_verilator.sh --build --run ../sw/bin/test/test_compute.hex
run_in verilator oseda ./run_verilator.sh --build --run ../sw/bin/test/test_gpio.hex
# (enable iDMA) run_in verilator oseda ./run_verilator.sh --build --run ../sw/bin/test/test_idma.hex
run_in verilator oseda ./run_verilator.sh --build --run ../sw/bin/test/test_interrupts.hex
run_in verilator oseda ./run_verilator.sh --build --run ../sw/bin/test/test_obi_timer.hex
run_in verilator oseda ./run_verilator.sh --build --run ../sw/bin/test/test_soc_ctrl.hex
run_in verilator oseda ./run_verilator.sh --build --run ../sw/bin/test/test_fft.hex
run_in verilator oseda ./run_verilator.sh --build --run ../sw/bin/test/test_sram.hex
run_in verilator oseda ./run_verilator.sh --build --run ../sw/bin/benchmark_fft.hex
# spectrum-analyzer demo (synthetic tone source; prints a UART spectrum)
run_in verilator oseda ./run_verilator.sh --build --run ../sw/bin/spectrum_analyzer.hex
# spectrum-analyzer over the I2S peripheral (tb i2s_mic_model feeds a tone)
run_in verilator oseda ./run_verilator.sh --build --run ../sw/bin/spectrum_analyzer_i2s.hex

echo "### Simulation (Questa/ModelSim)"
echo "TODO"