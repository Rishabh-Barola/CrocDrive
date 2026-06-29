#!/usr/bin/env bash
set -u
set -o pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
STAMP="$(date +%Y%m%d_%H%M%S)"
LOGDIR="$ROOT/logs/final_frontend_${STAMP}"
mkdir -p "$LOGDIR"

PASS=()
FAIL=()
SKIP=()

RUN_TECH_SETUP="${RUN_TECH_SETUP:-1}"
RUN_LEGACY_QEN_VELOCITY="${RUN_LEGACY_QEN_VELOCITY:-1}"

if command -v riscv64-unknown-elf-gcc >/dev/null 2>&1 && command -v verilator >/dev/null 2>&1; then
  USE_OSEDA=0
else
  USE_OSEDA=1
fi

env_run() {
  if [[ "$USE_OSEDA" -eq 1 ]]; then
    oseda "$@"
  else
    "$@"
  fi
}

record_pass() { PASS+=("$1"); echo "### PASS: $1"; }
record_fail() { FAIL+=("$1"); echo "### FAIL: $1"; }
record_skip() { SKIP+=("$1"); echo "### SKIP: $1"; }

run_logged() {
  local name="$1"
  shift
  local logfile="$LOGDIR/${name}.log"

  echo
  echo "============================================================"
  echo "RUN: $name"
  echo "CMD: $*"
  echo "LOG: $logfile"
  echo "============================================================"

  (
    cd "$ROOT"
    "$@"
  ) >"$logfile" 2>&1

  local rc=$?
  if [[ $rc -eq 0 ]]; then
    record_pass "$name"
  else
    record_fail "$name"
    echo "---- tail $logfile ----"
    tail -120 "$logfile"
  fi
}

run_setup() {
  echo
  echo "============================================================"
  echo "0. Technology setup"
  echo "============================================================"

  if [[ "$RUN_TECH_SETUP" != "1" ]]; then
    record_skip "technology_setup_disabled"
    return
  fi

  run_logged "setup_git_submodules" git submodule update --init --recursive

  if command -v icdesign >/dev/null 2>&1; then
    run_logged "setup_icdesign_ihp13" icdesign ihp13 -update all -nogui
  else
    record_fail "setup_icdesign_ihp13: icdesign command not found"
  fi
}

check_tools() {
  local logfile="$LOGDIR/tool_check.log"

  {
    echo "### Tool locations"
    command -v oseda || true
    command -v icdesign || true
    command -v verilator || true
    command -v riscv64-unknown-elf-gcc || true

    echo
    echo "### Tool versions"
    env_run verilator --version || true
    env_run riscv64-unknown-elf-gcc --version | head -5 || true
  } >"$logfile" 2>&1

  if env_run verilator --version >/dev/null 2>&1 && \
     env_run riscv64-unknown-elf-gcc --version >/dev/null 2>&1; then
    record_pass "tool_check"
  else
    record_fail "tool_check"
    tail -120 "$logfile"
  fi
}

check_source_inclusion() {
  local logfile="$LOGDIR/source_inclusion.log"

  {
    cd "$ROOT"

    echo "### Git status"
    git status --short || true

    echo
    echo "### Bender entries"
    grep -n "pwm_core\|qen_core\|user_amcp\|user_domain" Bender.yml || true

    echo
    echo "### RTL files"
    ls -lh \
      rtl/user_domain/pwm_core.sv \
      rtl/user_domain/qen_core.sv \
      rtl/user_domain/user_amcp.sv \
      rtl/user_domain.sv \
      rtl/user_pkg.sv || true

    echo
    echo "### AMCP/QEN/PWM references"
    grep -RIn "pwm_core\|qen_core\|qen_\|pwm_" rtl/user_domain rtl/user_domain.sv rtl/user_pkg.sv Bender.yml | head -300 || true
  } >"$logfile" 2>&1

  if grep -q "qen_core" "$logfile" && \
     grep -q "pwm_core" "$logfile" && \
     grep -q "user_amcp" "$logfile"; then
    record_pass "source_inclusion"
  else
    record_fail "source_inclusion"
    tail -160 "$logfile"
  fi
}

run_sv_tb() {
  local name="$1"
  local dir="$2"
  local dut="$3"
  local required="${4:-1}"
  shift 4
  local pre_cmds=("$@")

  local logfile="$LOGDIR/rtl_${name}.log"

  if [[ ! -d "$ROOT/$dir" ]]; then
    if [[ "$required" == "1" ]]; then
      record_fail "rtl_${name}: missing directory $dir"
    else
      record_skip "rtl_${name}: missing directory $dir"
    fi
    return
  fi

  local tbfile
  tbfile="$(find "$ROOT/$dir" -maxdepth 1 \( -name "tb*.sv" -o -name "*tb*.sv" \) | head -1)"

  if [[ -z "$tbfile" || ! -f "$tbfile" ]]; then
    if [[ "$required" == "1" ]]; then
      record_fail "rtl_${name}: no tb sv file in $dir"
    else
      record_skip "rtl_${name}: no tb sv file in $dir"
    fi
    return
  fi

  local top
  top="$(grep -E "^[[:space:]]*module[[:space:]]+" "$tbfile" | head -1 | sed -E 's/^[[:space:]]*module[[:space:]]+([A-Za-z0-9_]+).*/\1/')"

  if [[ -z "$top" ]]; then
    record_fail "rtl_${name}: could not infer top module"
    return
  fi

  echo
  echo "============================================================"
  echo "RTL TB: $name"
  echo "DIR : $dir"
  echo "DUT : $dut"
  echo "TB  : $(basename "$tbfile")"
  echo "TOP : $top"
  echo "LOG : $logfile"
  echo "============================================================"

  (
    cd "$ROOT/$dir"

    rm -rf obj_dir

    for cmd in "${pre_cmds[@]}"; do
      if [[ -n "$cmd" ]]; then
        echo "### PRE: $cmd"
        bash -lc "$cmd"
      fi
    done

    env_run verilator \
      -Wno-fatal \
      -Wno-style \
      -Wno-WIDTHTRUNC \
      -Wno-WIDTHEXPAND \
      -Wno-UNUSED \
      --binary \
      --timing \
      --trace-fst \
      --top "$top" \
      "$ROOT/$dut" \
      "$tbfile"

    env_run "./obj_dir/V${top}"
  ) >"$logfile" 2>&1

  local rc=$?

  if [[ $rc -eq 0 ]] && grep -Eqi "PASS|PASSED|SUCCESS" "$logfile"; then
    record_pass "rtl_${name}"
  else
    if [[ "$required" == "1" ]]; then
      record_fail "rtl_${name}"
    else
      record_skip "rtl_${name}: optional legacy/non-required failed"
    fi
    echo "---- tail $logfile ----"
    tail -160 "$logfile"
  fi
}

build_sw_all() {
  echo
  echo "============================================================"
  echo "2. Software build"
  echo "============================================================"

  local logfile="$LOGDIR/sw_make.log"

  (
    cd "$ROOT/sw"
    env_run make
  ) >"$logfile" 2>&1

  local rc=$?
  if [[ $rc -eq 0 ]]; then
    record_pass "sw_make"
  else
    record_fail "sw_make"
    tail -160 "$logfile"
  fi
}

run_soc_test() {
  local test="$1"
  local build_log="$LOGDIR/build_${test}.log"
  local run_log="$LOGDIR/verilator_${test}.log"

  echo
  echo "============================================================"
  echo "SOC TEST: $test"
  echo "============================================================"

  if [[ ! -f "$ROOT/sw/test/${test}.c" ]]; then
    record_skip "verilator_${test}: missing sw/test/${test}.c"
    return
  fi

  (
    cd "$ROOT/sw"
    env_run make "bin/test/${test}.hex"
  ) >"$build_log" 2>&1

  if [[ $? -ne 0 || ! -f "$ROOT/sw/bin/test/${test}.hex" ]]; then
    record_fail "build_${test}"
    tail -100 "$build_log"
    return
  fi

  record_pass "build_${test}"

  (
    cd "$ROOT/verilator"
    env_run ./run_verilator.sh --run "../sw/bin/test/${test}.hex"
  ) >"$run_log" 2>&1

  if grep -q "Simulation finished: SUCCESS" "$run_log"; then
    record_pass "verilator_${test}"
  else
    record_fail "verilator_${test}"
    tail -160 "$run_log"
  fi
}

build_verilator_once() {
  local logfile="$LOGDIR/verilator_build_helloworld.log"

  echo
  echo "============================================================"
  echo "3. Build Croc Verilator model once"
  echo "============================================================"

  (
    cd "$ROOT/verilator"
    rm -rf obj_dir
    env_run ./run_verilator.sh --flist
    env_run ./run_verilator.sh --build --run ../sw/bin/helloworld.hex
  ) >"$logfile" 2>&1

  if grep -q "Simulation finished: SUCCESS" "$logfile"; then
    record_pass "verilator_build_helloworld"
  else
    record_fail "verilator_build_helloworld"
    tail -160 "$logfile"
  fi
}

summary() {
  local summary_file="$LOGDIR/SUMMARY.txt"

  {
    echo "============================================================"
    echo "Final frontend/regression summary"
    echo "TIME: $(date)"
    echo "ROOT: $ROOT"
    echo "LOGDIR: $LOGDIR"
    echo "USE_OSEDA: $USE_OSEDA"
    echo "RUN_TECH_SETUP: $RUN_TECH_SETUP"
    echo "RUN_LEGACY_QEN_VELOCITY: $RUN_LEGACY_QEN_VELOCITY"
    echo "============================================================"
    echo
    echo "PASS (${#PASS[@]}):"
    printf '  %s\n' "${PASS[@]}"
    echo
    echo "SKIP (${#SKIP[@]}):"
    printf '  %s\n' "${SKIP[@]}"
    echo
    echo "FAIL (${#FAIL[@]}):"
    printf '  %s\n' "${FAIL[@]}"
  } | tee "$summary_file"

  echo
  echo "Summary written to: $summary_file"

  if [[ ${#FAIL[@]} -ne 0 ]]; then
    exit 1
  fi
}

echo "============================================================"
echo "Final frontend/regression"
echo "ROOT=$ROOT"
echo "LOGDIR=$LOGDIR"
echo "TIME=$(date)"
echo "============================================================"

run_setup
check_tools
check_source_inclusion

echo
echo "============================================================"
echo "1. Standalone RTL unit testbenches"
echo "============================================================"

run_sv_tb "pwm_core_basic" \
  "rtl/user_domain/tb" \
  "rtl/user_domain/pwm_core.sv" \
  1

run_sv_tb "pwm_core_file" \
  "rtl/user_domain/tb/pwm_core_file_tb" \
  "rtl/user_domain/pwm_core.sv" \
  1 \
  "python3 gen_stimuli.py" \
  "python3 gen_exp_response.py"

run_sv_tb "qen_core_file" \
  "rtl/user_domain/tb/qen_core_file_tb" \
  "rtl/user_domain/qen_core.sv" \
  1 \
  "python3 gen_qen_vectors.py"

run_sv_tb "qen_core_velocity_stress" \
  "rtl/user_domain/tb/qen_core_velocity_stress_tb" \
  "rtl/user_domain/qen_core.sv" \
  1

if [[ "$RUN_LEGACY_QEN_VELOCITY" == "1" ]]; then
  run_sv_tb "qen_core_velocity_legacy" \
    "rtl/user_domain/tb/qen_core_velocity_tb" \
    "rtl/user_domain/qen_core.sv" \
    0
else
  record_skip "rtl_qen_core_velocity_legacy_disabled"
fi

build_sw_all
build_verilator_once

echo
echo "============================================================"
echo "4. Croc SoC firmware tests through Verilator"
echo "============================================================"

BASIC_TESTS=(
  print_config
  test_soc_ctrl
  test_uart
  test_gpio
  test_clint
  test_interrupts
  test_compute
  test_obi_timer
  test_sram
)

AMCP_TESTS=(
  test_pwm
  test_qen
  test_qen_verbose
  test_qen_gpio
  test_qen_gpio_verbose
  benchmark_pwm
  benchmark_qen
  waveform_pwm_compare
)

SYSTEM_TESTS=(
  motor_pid_closed_loop
  buck_pid_demo
)

for t in "${BASIC_TESTS[@]}"; do
  run_soc_test "$t"
done

for t in "${AMCP_TESTS[@]}"; do
  run_soc_test "$t"
done

for t in "${SYSTEM_TESTS[@]}"; do
  run_soc_test "$t"
done

echo
echo "============================================================"
echo "5. Power workload build checks"
echo "============================================================"

for t in power_amcp_stress power_sw_pwm_stress; do
  if [[ -f "$ROOT/sw/test/${t}.c" ]]; then
    (
      cd "$ROOT/sw"
      env_run make "bin/test/${t}.hex"
    ) >"$LOGDIR/build_${t}.log" 2>&1

    if [[ $? -eq 0 && -f "$ROOT/sw/bin/test/${t}.hex" ]]; then
      record_pass "build_${t}"
    else
      record_fail "build_${t}"
      tail -100 "$LOGDIR/build_${t}.log"
    fi
  else
    record_skip "build_${t}: source missing"
  fi
done

summary
