#!/usr/bin/env bash
set -u
set -o pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
STAMP="$(date +%Y%m%d_%H%M%S)"
LOGDIR="$ROOT/logs/backend_signoff_$STAMP"
mkdir -p "$LOGDIR"

RUN_SETUP="${RUN_SETUP:-0}"
RUN_YOSYS="${RUN_YOSYS:-1}"
RUN_OPENROAD="${RUN_OPENROAD:-1}"
RUN_DEF2GDS="${RUN_DEF2GDS:-1}"
RUN_DRC="${RUN_DRC:-1}"
RUN_V2SPICE="${RUN_V2SPICE:-1}"
RUN_LVS="${RUN_LVS:-1}"
CLEAN="${CLEAN:-1}"

PASS=()
FAIL=()
SKIP=()

if command -v riscv64-unknown-elf-gcc >/dev/null 2>&1 && command -v openroad >/dev/null 2>&1; then
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

die() {
  echo
  echo "### FATAL: $*"
  summary || true
  exit 1
}

run_in() {
  local dir="$1"
  local name="$2"
  shift 2
  local logfile="$LOGDIR/${name}.log"

  echo
  echo "============================================================"
  echo "RUN: $name"
  echo "DIR: $dir"
  echo "CMD: $*"
  echo "LOG: $logfile"
  echo "============================================================"

  (
    cd "$ROOT/$dir"
    "$@"
  ) >"$logfile" 2>&1

  local rc=$?
  if [[ $rc -eq 0 ]]; then
    record_pass "$name"
  else
    record_fail "$name"
    echo "---- tail $logfile ----"
    tail -120 "$logfile"
    return 1
  fi
}

run_in_oseda() {
  local dir="$1"
  local name="$2"
  shift 2
  run_in "$dir" "$name" env_run "$@"
}

run_first_existing() {
  local dir="$1"
  local name="$2"
  shift 2

  for script in "$@"; do
    if [[ -x "$ROOT/$dir/$script" ]]; then
      run_in_oseda "$dir" "$name" "$script"
      return $?
    fi
  done

  record_fail "$name: none of these scripts exists/executable: $*"
  return 1
}

summary() {
  local summary_file="$LOGDIR/SUMMARY.txt"

  {
    echo "============================================================"
    echo "Backend signoff summary"
    echo "TIME: $(date)"
    echo "ROOT: $ROOT"
    echo "LOGDIR: $LOGDIR"
    echo "USE_OSEDA: $USE_OSEDA"
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
}

echo "============================================================"
echo "Backend signoff"
echo "ROOT        = $ROOT"
echo "LOGDIR      = $LOGDIR"
echo "TIME        = $(date)"
echo "USE_OSEDA   = $USE_OSEDA"
echo "CLEAN       = $CLEAN"
echo "RUN_SETUP   = $RUN_SETUP"
echo "RUN_YOSYS   = $RUN_YOSYS"
echo "RUN_OPENROAD= $RUN_OPENROAD"
echo "RUN_DEF2GDS = $RUN_DEF2GDS"
echo "RUN_DRC     = $RUN_DRC"
echo "RUN_V2SPICE = $RUN_V2SPICE"
echo "RUN_LVS     = $RUN_LVS"
echo "============================================================"

echo
echo "### Script inventory"
{
  echo "### OpenROAD run scripts"
  find "$ROOT/openroad" -maxdepth 1 -type f -perm -u+x -printf "%f\n" 2>/dev/null | sort

  echo
  echo "### KLayout run scripts"
  find "$ROOT/klayout" -maxdepth 1 -type f -perm -u+x -printf "%f\n" 2>/dev/null | sort

  echo
  echo "### Yosys run scripts"
  find "$ROOT/yosys" -maxdepth 1 -type f -perm -u+x -printf "%f\n" 2>/dev/null | sort
} | tee "$LOGDIR/script_inventory.txt"

if [[ "$RUN_SETUP" == "1" ]]; then
  echo
  echo "============================================================"
  echo "0. Technology setup"
  echo "============================================================"

  run_in "." "setup_git_submodules" git submodule update --init --recursive || die "submodule setup failed"

  if command -v icdesign >/dev/null 2>&1; then
    run_in "." "setup_icdesign_ihp13" icdesign ihp13 -update all -nogui || die "icdesign setup failed"
  else
    record_fail "setup_icdesign_ihp13: icdesign not found"
    die "icdesign not found"
  fi
else
  record_skip "technology_setup"
fi

echo
echo "============================================================"
echo "Tool check"
echo "============================================================"

{
  echo "### Tool locations"
  command -v oseda || true
  command -v openroad || true
  command -v klayout || true
  command -v yosys || true
  command -v verilator || true
  command -v riscv64-unknown-elf-gcc || true

  echo
  echo "### Tool versions"
  env_run openroad -version || true
  env_run yosys -V || true
  env_run verilator --version || true
} > "$LOGDIR/tool_check.log" 2>&1

record_pass "tool_check"

if [[ "$RUN_YOSYS" == "1" ]]; then
  echo
  echo "============================================================"
  echo "1. Yosys synthesis"
  echo "============================================================"

  if [[ "$CLEAN" == "1" ]]; then
    rm -rf "$ROOT/yosys/out" "$ROOT/yosys/tmp" "$ROOT/yosys/reports" "$ROOT/yosys/build"
  fi

  run_in_oseda "yosys" "yosys_flist" ./run_synthesis.sh --flist || die "Yosys flist failed"
  run_in_oseda "yosys" "yosys_synth" ./run_synthesis.sh --synth || die "Yosys synthesis failed"

  echo
  echo "### Synthesis inclusion checks"

  {
    cd "$ROOT"

    echo "### AMCP/PWM/QEN evidence"
    grep -RIn "user_amcp\|pwm\|PWM\|qen\|QEN\|index_position\|error_count" \
      yosys/out yosys/tmp yosys/reports 2>/dev/null | head -250 || true

    echo
    echo "### SRAM macro evidence"
    grep -RIn "RM_IHPSG13_1P_1024x64\|1024x64\|gen_2048x32xBx1" \
      yosys/out yosys/tmp yosys/reports 2>/dev/null | head -160 || true

    echo
    echo "### RV32M/multiplier evidence"
    grep -RIn "cve2_multdiv\|multdiv\|RV32M\|mul" \
      yosys/out yosys/tmp yosys/reports 2>/dev/null | head -160 || true
  } > "$LOGDIR/yosys_inclusion_check.log" 2>&1

  if grep -qi "user_amcp" "$LOGDIR/yosys_inclusion_check.log" && \
     grep -qi "qen\|QEN" "$LOGDIR/yosys_inclusion_check.log" && \
     grep -qi "1024x64" "$LOGDIR/yosys_inclusion_check.log"; then
    record_pass "yosys_inclusion_check"
  else
    record_fail "yosys_inclusion_check"
    tail -160 "$LOGDIR/yosys_inclusion_check.log"
    die "Yosys inclusion check failed"
  fi
else
  record_skip "yosys"
fi

if [[ "$RUN_OPENROAD" == "1" ]]; then
  echo
  echo "============================================================"
  echo "2. OpenROAD physical flow"
  echo "============================================================"

  if [[ "$CLEAN" == "1" ]]; then
    rm -rf "$ROOT/openroad/out" "$ROOT/openroad/save" "$ROOT/openroad/reports" "$ROOT/openroad/logs"
  fi

  mkdir -p "$ROOT/openroad/out" "$ROOT/openroad/save" "$ROOT/openroad/reports" "$ROOT/openroad/logs"

  # Prefer single full-flow script if your repo has one. Otherwise run stages.
  if [[ -x "$ROOT/openroad/run_openroad.sh" ]]; then
    run_in_oseda "openroad" "openroad_full" ./run_openroad.sh || die "OpenROAD full flow failed"
  elif [[ -x "$ROOT/openroad/run_flow.sh" ]]; then
    run_in_oseda "openroad" "openroad_full" ./run_flow.sh || die "OpenROAD full flow failed"
  else
    run_first_existing "openroad" "openroad_floorplan" \
      ./run_floorplan.sh ./run_01_floorplan.sh || die "OpenROAD floorplan failed"

    echo
    echo "### Optional power-grid check after floorplan"
    run_in_oseda "openroad" "openroad_power_grid_check" openroad -no_init <<'EOC' || true
source scripts/startup.tcl
load_checkpoint 01_croc.floorplan
puts "### check_power_grid VDD"
catch {check_power_grid -net VDD} result_vdd
puts $result_vdd
puts "### check_power_grid VSS"
catch {check_power_grid -net VSS} result_vss
puts $result_vss
exit
EOC

    run_first_existing "openroad" "openroad_place" \
      ./run_placement.sh ./run_place.sh ./run_02_placement.sh ./run_02_place.sh || die "OpenROAD placement failed"

    run_first_existing "openroad" "openroad_cts" \
      ./run_cts.sh ./run_03_cts.sh || die "OpenROAD CTS failed"

    run_first_existing "openroad" "openroad_route" \
      ./run_routing.sh ./run_route.sh ./run_04_routing.sh ./run_04_route.sh || die "OpenROAD route failed"

    run_first_existing "openroad" "openroad_finish" \
      ./run_finishing.sh ./run_finish.sh ./run_05_finishing.sh ./run_05_finish.sh || die "OpenROAD finishing failed"
  fi

  echo
  echo "### OpenROAD final output check"

  {
    cd "$ROOT/openroad"

    echo "### Expected files"
    ls -lh out/croc.def out/croc.v out/croc_lvs.v save/05_croc.final.zip 2>/dev/null || true

    echo
    echo "### Final area"
    grep -RIn "Design Area Summary\|Die Area\|Core Area\|Total Area\|Std Cell Utilization\|Core Utilization" \
      reports 2>/dev/null | tail -80 || true

    echo
    echo "### DRC/timing/route warning grep"
    grep -RIn "ERROR\|VIOLATED\|unconnected\|disconnected\|PDN-0110\|No via inserted" \
      logs reports 2>/dev/null | head -250 || true

    echo
    echo "### AMCP/SRAM final hierarchy evidence"
    grep -RIn "i_user_amcp\|gen_sram_bank\|1024x64\|RM_IHPSG13" \
      reports out 2>/dev/null | head -250 || true
  } > "$LOGDIR/openroad_final_check.log" 2>&1

  if [[ -f "$ROOT/openroad/out/croc.def" && -f "$ROOT/openroad/out/croc.v" ]]; then
    record_pass "openroad_final_outputs_exist"
  else
    record_fail "openroad_final_outputs_exist"
    tail -160 "$LOGDIR/openroad_final_check.log"
    die "OpenROAD final outputs missing"
  fi
else
  record_skip "openroad"
fi

if [[ "$RUN_DEF2GDS" == "1" || "$RUN_DRC" == "1" || "$RUN_V2SPICE" == "1" || "$RUN_LVS" == "1" ]]; then
  echo
  echo "============================================================"
  echo "3. KLayout / signoff preparation"
  echo "============================================================"

  if [[ "$CLEAN" == "1" ]]; then
    rm -rf "$ROOT/klayout/out" "$ROOT/klayout/drc/out" "$ROOT/klayout/lvs/out" 2>/dev/null || true
  fi
fi

if [[ "$RUN_DEF2GDS" == "1" ]]; then
  echo
  echo "============================================================"
  echo "3a. DEF to GDS"
  echo "============================================================"

  run_first_existing "klayout" "klayout_def2gds" \
    ./def2gds-croc ./run_def2gds-croc ./def2gds.sh || die "DEF to GDS failed"

  if [[ -x "$ROOT/klayout/run_finishing-croc" ]]; then
    run_in_oseda "klayout" "klayout_finishing" ./run_finishing-croc || die "KLayout finishing failed"
  else
    record_skip "klayout_finishing: run_finishing-croc missing"
  fi

  {
    cd "$ROOT"
    echo "### GDS files"
    find klayout openroad -maxdepth 4 -type f \( -name "*.gds" -o -name "*.gds.gz" \) -ls 2>/dev/null | sort || true
  } > "$LOGDIR/gds_files.log" 2>&1
fi

if [[ "$RUN_DRC" == "1" ]]; then
  echo
  echo "============================================================"
  echo "3b. DRC"
  echo "============================================================"

  run_first_existing "klayout" "klayout_drc" \
    ./run_drc-croc ./drc-croc ./run_drc.sh || die "DRC command failed. Fix DRC patches, then rerun from KLayout."

  {
    cd "$ROOT"
    echo "### DRC result files"
    find klayout -maxdepth 5 -type f \( -name "*.lyrdb" -o -iname "*drc*.rpt" -o -iname "*drc*.log" \) -ls 2>/dev/null | sort || true

    echo
    echo "### DRC grep"
    grep -RIn "violation\|Violation\|ERROR\|FAILED\|Total\|clean\|Clean" klayout 2>/dev/null | head -250 || true
  } > "$LOGDIR/drc_result_check.log" 2>&1

  record_pass "drc_result_files_collected"
fi

if [[ "$RUN_V2SPICE" == "1" ]]; then
  echo
  echo "============================================================"
  echo "3c. Verilog to SPICE"
  echo "============================================================"

  if [[ -x "$ROOT/klayout/verilog2spice-croc" ]]; then
    run_in_oseda "klayout" "verilog2spice" ./verilog2spice-croc || die "Verilog to SPICE failed"
  elif [[ -x "$ROOT/klayout/run_verilog2spice-croc" ]]; then
    run_in_oseda "klayout" "verilog2spice" ./run_verilog2spice-croc || die "Verilog to SPICE failed"
  elif [[ -x "$ROOT/klayout/run_v2spice-croc" ]]; then
    run_in_oseda "klayout" "verilog2spice" ./run_v2spice-croc || die "Verilog to SPICE failed"
  else
    record_skip "verilog2spice: no standalone script found; run_lvs-croc may generate it internally"
  fi

  {
    cd "$ROOT"
    echo "### SPICE/CDL files"
    find . -maxdepth 6 -type f \( -name "*.spice" -o -name "*.sp" -o -name "*.cdl" -o -name "*lvs*.v" \) -ls 2>/dev/null | sort || true
  } > "$LOGDIR/spice_files.log" 2>&1
fi

if [[ "$RUN_LVS" == "1" ]]; then
  echo
  echo "============================================================"
  echo "3d. LVS"
  echo "============================================================"

  run_first_existing "klayout" "klayout_lvs" \
    ./run_lvs-croc ./lvs-croc ./run_lvs.sh || die "LVS failed"

  {
    cd "$ROOT"
    echo "### LVS result files"
    find klayout -maxdepth 6 -type f \( -iname "*lvs*" -o -iname "*.spice" -o -iname "*.cdl" \) -ls 2>/dev/null | sort || true

    echo
    echo "### LVS grep"
    grep -RIn "LVS\|MATCH\|CORRECT\|clean\|Clean\|failed\|FAILED\|error\|ERROR\|Netlists" klayout 2>/dev/null | head -300 || true
  } > "$LOGDIR/lvs_result_check.log" 2>&1

  record_pass "lvs_result_files_collected"
fi

echo
echo "============================================================"
echo "4. Final signoff artifact inventory"
echo "============================================================"

{
  cd "$ROOT"

  echo "### Key OpenROAD outputs"
  ls -lh openroad/out/croc.def openroad/out/croc.v openroad/out/croc_lvs.v openroad/save/05_croc.final.zip 2>/dev/null || true

  echo
  echo "### GDS"
  find klayout openroad -maxdepth 5 -type f \( -name "*.gds" -o -name "*.gds.gz" \) -ls 2>/dev/null | sort || true

  echo
  echo "### DRC"
  find klayout -maxdepth 6 -type f \( -name "*.lyrdb" -o -iname "*drc*.rpt" -o -iname "*drc*.log" \) -ls 2>/dev/null | sort || true

  echo
  echo "### LVS/SPICE"
  find klayout -maxdepth 6 -type f \( -iname "*lvs*" -o -name "*.spice" -o -name "*.sp" -o -name "*.cdl" \) -ls 2>/dev/null | sort || true
} | tee "$LOGDIR/final_artifact_inventory.txt"

summary

if [[ ${#FAIL[@]} -ne 0 ]]; then
  exit 1
fi

echo
echo "### Backend signoff script completed."
echo "### Logs: $LOGDIR"
