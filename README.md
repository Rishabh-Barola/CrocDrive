# CrocDrive

**CrocDrive** extends the [Croc RISC-V SoC](https://github.com/pulp-platform/croc) with a memory-mapped **Advanced Motor-Control Peripheral (AMCP)** for deterministic embedded-control I/O.

The project was developed for the **VLSI 2 course at ETH Zürich** and was taken through RTL design, verification, synthesis, place-and-route, timing analysis, power analysis, IR-drop analysis, DRC and LVS using the IHP SG13G2 130 nm technology.

The main design idea is to keep high-level control algorithms in software while moving timing-critical operations into hardware. CrocDrive therefore adds dedicated hardware for:

* PWM generation
* quadrature-encoder decoding
* position, direction and index tracking
* encoder error detection
* GPIO alternate-function routing
* software-visible status and control registers

The existing CVE2 core, OBI-based programming model and Croc pad interface are preserved.

---

## Project Overview

CrocDrive adds an **Advanced Motor-Control Peripheral (AMCP)** inside Croc's `user_domain`.

AMCP contains two main datapaths:

* **PWM core** — generates deterministic PWM waveforms after one-time software configuration.
* **QEN core** — continuously decodes quadrature A/B transitions and tracks signed position, direction, index events and invalid transitions.

AMCP is exposed as a normal memory-mapped OBI subordinate, so software interacts with it using ordinary RISC-V loads and stores.

The project also includes:

* two enlarged 8 KiB SRAM banks for a total of 16 KiB
* RV32MFast support in CVE2
* standalone RTL verification
* full-system Verilator firmware tests
* hardware-versus-software CPU-offload benchmarks
* motor-control and buck-converter closed-loop demonstrations
* complete backend implementation in OpenROAD
* final GDS generation and physical verification

For the complete architecture, implementation details, verification methodology and physical-design results, see the project report in the repository.

---

## Architecture

CrocDrive keeps the overall Croc architecture unchanged.

The baseline Croc domain contains the CVE2 processor, SRAM, OBI interconnect, UART, GPIO, timer, debug infrastructure and other standard peripherals. The project extends the separate `user_domain` with:

* a user identification ROM
* the AMCP peripheral

AMCP is connected as an OBI subordinate and therefore does not require modifications to the processor instruction set.

The PWM output reaches the chip boundary through the existing GPIO interface rather than through additional pads.

### GPIO assignment

| GPIO  | CrocDrive function            |
| ----- | ----------------------------- |
| GPIO0 | PWM alternate-function output |
| GPIO1 | Quadrature encoder A          |
| GPIO2 | Quadrature encoder B          |
| GPIO3 | Quadrature encoder Z / index  |

When the AMCP alternate function is disabled, the normal Croc GPIO behavior is preserved.

---

## Memory Map

The relevant CrocDrive memory regions are:

| Start address | End address   | Region                  |
| ------------- | ------------- | ----------------------- |
| `0x1000_0000` | `0x1000_2000` | SRAM bank 0 — 8 KiB     |
| `0x1000_2000` | `0x1000_4000` | SRAM bank 1 — 8 KiB     |
| `0x2000_0000` | `0x2000_1000` | User identification ROM |
| `0x2000_1000` | `0x2000_2000` | AMCP                    |

The user ROM stores a zero-terminated identification string while AMCP occupies its own 4 KiB OBI address window.

---

## AMCP Register Map

AMCP base address:

`0x2000_1000`

| Offset  | Register             | Access    | Purpose                              |
| ------- | -------------------- | --------- | ------------------------------------ |
| `0x000` | `AMCP_ID`            | R         | Peripheral identifier                |
| `0x004` | `AMCP_VERSION`       | R         | Peripheral version                   |
| `0x008` | `AMCP_PINMUX`        | R/W       | GPIO alternate-function control      |
| `0x00C` | `AMCP_STATUS`        | R         | Global status                        |
| `0x010` | `PWM_CTRL`           | R/W       | PWM enable and polarity              |
| `0x014` | `PWM_PERIOD`         | R/W       | Configured PWM period                |
| `0x018` | `PWM_DUTY`           | R/W       | Configured PWM duty                  |
| `0x01C` | `PWM_COUNTER`        | R         | Current PWM counter                  |
| `0x020` | `PWM_STATUS`         | R/W1C     | Sticky PWM status flags              |
| `0x024` | `PWM_DUTY_ACTIVE`    | R         | Active duty value                    |
| `0x028` | `PWM_PERIOD_ACTIVE`  | R         | Active period value                  |
| `0x040` | `QEN_CTRL`           | R/W + W1P | QEN configuration and clear commands |
| `0x044` | `QEN_STATUS`         | R         | QEN state and status                 |
| `0x048` | `QEN_POSITION`       | R         | Signed position                      |
| `0x04C` | `QEN_VELOCITY`       | R         | Position change over sample window   |
| `0x050` | `QEN_DELTA`          | R         | Last sampled position delta          |
| `0x054` | `QEN_INDEX_POSITION` | R         | Position captured on index pulse     |
| `0x058` | `QEN_ERROR_COUNT`    | R         | Invalid-transition count             |
| `0x05C` | `QEN_SAMPLE_PERIOD`  | R/W       | Velocity sample interval             |
| `0x060` | `QEN_SIM_INPUT`      | R/W       | Software-driven `{Z,B,A}` inputs     |
| `0x064` | `QEN_DEBUG`          | R         | Decoder/debug state                  |

---

## PWM Core

The PWM generator uses a 16-bit counter and independent configuration and active registers.

Software writes the requested period and duty values, while the PWM core transfers them to the active datapath only at safe update points. This prevents a mid-period register write from corrupting the currently generated pulse.

For an active period `N`:

`f_PWM = f_clk / N`

and the duty-cycle step is:

`1 / N`

For example, at a 100 MHz system clock with a period of 100 cycles, the PWM frequency is 1 MHz with 1% duty-cycle resolution.

The implementation also handles edge conditions explicitly:

* period equal to zero disables the active waveform
* duty greater than the period is clamped to the period
* disabling PWM forces the output low

---

## Quadrature Encoder Core

The QEN core continuously observes the A/B encoder signals and classifies each state transition as:

* forward
* reverse
* unchanged
* invalid

Valid transitions increment or decrement the signed position counter. Invalid two-bit transitions increment an error counter without changing the position.

The optional Z/index input captures the current encoder position and can optionally reset the live position counter.

QEN also computes position change over a configurable sampling interval, allowing firmware to obtain a digital velocity-like measurement without decoding every edge in software.

For deterministic verification, the encoder inputs can either come from GPIO1–GPIO3 or from the software-controlled `QEN_SIM_INPUT` register.

---

## Verification

CrocDrive is verified at several levels.

### Standalone RTL verification

The PWM and QEN cores are first tested independently of the full SoC.

Relevant testbench directories include:

* `rtl/user_domain/tb/`
* `rtl/user_domain/tb/pwm_core_file_tb/`
* `rtl/user_domain/tb/qen_core_file_tb/`
* `rtl/user_domain/tb/qen_core_velocity_stress_tb/`

Python scripts generate deterministic stimulus and expected-response vectors.

The QEN file-driven regression includes directed cases followed by 10,000 deterministic random vectors.

### Full-system firmware verification

The complete Croc SoC is then simulated with C firmware using Verilator.

The main AMCP tests include:

* `test_pwm`
* `test_qen`
* `test_qen_verbose`
* `test_qen_gpio`
* `test_qen_gpio_verbose`
* `benchmark_pwm`
* `benchmark_qen`
* `waveform_pwm_compare`

The regression also runs the original Croc tests for peripherals such as UART, GPIO, CLINT, SRAM and SoC control to check that the AMCP integration does not break baseline functionality.

### System demonstrations

Two higher-level demonstrations are included:

* `motor_pid_closed_loop`
* `buck_pid_demo`

The motor example combines QEN feedback with firmware control and PWM actuation.

The buck example uses the real AMCP PWM output together with a testbench plant model and ADC-like GPIO feedback. The analog power stage itself is modeled in simulation; CrocDrive implements the digital control interface.

---

## CPU-Offload Results

A central goal of CrocDrive is to reduce continuous CPU involvement in timing-sensitive I/O.

### PWM

| Generated periods | Software PWM cycles | Hardware setup cycles | CPU involvement reduction |
| ----------------: | ------------------: | --------------------: | ------------------------: |
|                10 |               1,643 |                    13 |                      126× |
|             1,000 |             164,003 |                    13 |                   12,615× |
|            10,000 |           1,640,003 |                    13 |                  126,154× |

The reduction refers to CPU work, not to PWM frequency. Hardware PWM is configured once and then continues autonomously.

A separate fixed-window test also showed that hardware PWM allowed the CPU to execute background work while maintaining the programmed waveform.

### QEN

| Encoder transitions | Software cycles | Hardware setup cycles |
| ------------------: | --------------: | --------------------: |
|                 100 |           2,124 |                   228 |
|                 400 |           8,424 |                   228 |
|               1,600 |          33,624 |                   228 |

For the 1,600-transition case, this corresponds to approximately 147.5× lower CPU involvement while producing the same final encoder position.

---

## Physical Implementation

The chip was implemented using the VLSI 2 backend flow:

**Bender → Yosys → OpenROAD → KLayout**

Important physical-design changes included:

* replacement of the original SRAM configuration with two `1024x64` SRAM macros
* updated SRAM floorplanning
* increased macro halo
* standard-cell placement padding
* correction of the mapped sequential-cell clock-pin name used during CTS
* clock-tree tuning
* conservative electrical-rule and timing repair
* antenna repair
* detailed routing
* final GDS generation
* DRC and LVS verification

### Submitted implementation

| Metric                      | Result                 |
| --------------------------- | ---------------------- |
| Technology                  | IHP SG13G2, 130 nm     |
| Supply                      | 1.2 V                  |
| System clock target         | 100 MHz                |
| Setup violations            | 0                      |
| Hold violations             | 0                      |
| Worst reported timing slack | approximately 1.13 ns  |
| OpenROAD die area           | 4.629 mm²              |
| Core area                   | 2.200 mm²              |
| Total reported area         | 2.638 mm²              |
| Active area                 | 0.995 mm²              |
| Standard-cell logic         | approximately 82.8 kGE |
| AMCP area                   | approximately 5.03 kGE |
| Final post-layout power     | approximately 67.8 mW  |

Residual OpenROAD electrical diagnostics remained for slew, capacitance and fanout. These are separate from GDS-level physical verification.

The final design passes LVS. The remaining DRC markers are confined to known off-grid/min-grid geometry inside the supplied SRAM macros; no project-specific GDS violations were observed outside those macros.

---

## Power and IR Drop

Representative workload-based VCD power results were:

| Workload            |       Full-chip power |
| ------------------- | --------------------: |
| Software PWM stress | approximately 52.3 mW |
| AMCP stress         | approximately 53.2 mW |

The approximately 0.9 mW difference corresponds to about 1.7% full-chip overhead in these workloads.

The main benefit of AMCP is therefore deterministic timing and CPU offload rather than an instantaneous reduction in full-chip power.

With the 15 pF I/O-load model, final post-layout power was approximately 67.8 mW, with the pad ring and clock network dominating the total.

Representative PDN analysis gave:

* worst VDD drop: approximately 17.1 mV
* worst VSS bounce: approximately 16.5 mV

---

# Building and Testing CrocDrive

## Requirements

The project uses the same overall tool environment as Croc.

On ETH systems, the recommended setup uses the internal IHP technology integration through `icdesign`.

From the repository root:

```sh
icdesign ihp13 -nogui
```

The open-source tool environment can also be entered using:

```sh
oseda bash
```

The repository uses [Bender](https://github.com/pulp-platform/bender) to manage RTL dependencies.

Initialize dependencies before the first build:

```sh
git submodule update --init --recursive
```

---

## Run the Complete Frontend Regression

The recommended verification command is:

```sh
./run_final_verilator_tests.sh
```

If the technology setup has already been performed:

```sh
RUN_TECH_SETUP=0 ./run_final_verilator_tests.sh
```

To disable the legacy QEN velocity regression:

```sh
RUN_TECH_SETUP=0 RUN_LEGACY_QEN_VELOCITY=0 ./run_final_verilator_tests.sh
```

Regression logs are written under:

`logs/final_frontend_<timestamp>/`

with a final `SUMMARY.txt`.

---

## Build Software Manually

Build all firmware:

```sh
cd sw
make
```

Build one test:

```sh
make bin/test/test_pwm.hex
```

Run it in Verilator:

```sh
cd ../verilator
./run_verilator.sh --flist
./run_verilator.sh --build --run ../sw/bin/test/test_pwm.hex
```

Once the Verilator model is built, other programs can be run directly:

```sh
./run_verilator.sh --run ../sw/bin/test/test_qen.hex
```

---

## RTL-to-GDS Flow

The normal Croc flow is:

```sh
cd yosys
./run_synthesis.sh --synth

cd ../openroad
./run_backend.sh --all

cd ../klayout
./run_finishing.sh --gds
```

The repository also contains project-specific helper scripts for frontend and backend regression.

Be careful when using backend cleanup scripts: some options remove existing synthesis, OpenROAD or KLayout outputs. Keep verified signoff results in a separate backup before rerunning physical implementation.

---

## Repository Structure

| Directory    | Purpose                                                  |
| ------------ | -------------------------------------------------------- |
| `rtl/`       | Croc and CrocDrive RTL, including standalone testbenches |
| `sw/`        | Firmware tests, benchmarks and demonstrations            |
| `verilator/` | Full-system Verilator simulation                         |
| `yosys/`     | Logic synthesis                                          |
| `openroad/`  | Floorplanning, placement, CTS and routing                |
| `klayout/`   | DEF-to-GDS finishing and physical verification           |
| `ihp13/`     | IHP SG13G2 technology integration                        |
| `doc/`       | Project documentation and report                         |
| `logs/`      | Regression and implementation logs                       |

Useful top-level scripts include:

* `run_amcp_frontend.sh`
* `run_final_verilator_tests.sh`
* `run_backend_signoff.sh`

---

# About Croc

[Croc](https://github.com/pulp-platform/croc) is a compact SoC designed for education and built using PULP IPs.

It contains:

* a CVE2 RISC-V processor
* SRAM
* an OBI crossbar
* UART
* GPIO
* CLINT
* timer
* JTAG/debug infrastructure
* a separate `user_domain` intended for student peripherals and accelerators

Croc is developed as part of the [PULP project](https://pulp-platform.org/), a joint effort between ETH Zürich and the University of Bologna.

The original Croc design was taped out in November 2024 as part of the [MLEM](http://asic.ee.ethz.ch/2024/MLEM.html) chip. Its core functionality was later verified on silicon.

CrocDrive preserves the main Croc programming and chip interfaces while extending the user domain with the AMCP hardware described above.

---

## Original Croc Configuration

The main Croc system configuration is defined in `rtl/croc_pkg.sv`.

Important parameters include:

| Parameter          | Purpose                         |
| ------------------ | ------------------------------- |
| `PulpJtagIdCode`   | JTAG/debug identification code  |
| `iDMAEnable`       | Optional DMA enable             |
| `NumSramBanks`     | Number of SRAM banks            |
| `SramBankNumWords` | Number of 32-bit words per bank |
| `BootAddr`         | Default boot address            |
| `CrocAddrMap`      | Main OBI crossbar address map   |
| `PeriphAddrMap`    | Peripheral address map          |

CrocDrive modifies the SRAM configuration and user-domain address map while keeping the overall architecture compatible with Croc.

---

## Boot

Croc currently boots through JTAG.

The existing Croc boot and debug infrastructure is preserved by CrocDrive.

---

## Bender

[Bender](https://github.com/pulp-platform/bender) manages the RTL dependencies used throughout Croc.

`Bender.yml` describes dependencies, source files and build targets.

`Bender.lock` stores the exact resolved dependency revisions.

Updating `Bender.lock` should be treated like modifying RTL: the full verification and implementation flow should be rerun afterward.

Technology-specific build contexts are selected using Bender targets such as `ihp13`.

---

## Known Limitations

* The motor and buck-converter plants are simulation models rather than analog circuitry integrated on-chip.
* QEN velocity is a digital position change over a configurable sample interval rather than a calibrated physical velocity.
* The software PWM benchmark uses polling-based GPIO bit-banging as the comparison baseline.
* Residual OpenROAD slew, capacitance and fanout diagnostics remain despite clean setup and hold timing.
* The supplied SRAM macro geometry produces known off-grid/min-grid DRC markers.

---

## Authors

**Chelsea Lai**
**Rishabh Barola**

ETH Zürich
VLSI 2 — 2026

---

## Acknowledgements

CrocDrive is based on the Croc SoC and the wider PULP ecosystem developed by ETH Zürich and the University of Bologna.

The project uses the IHP SG13G2 open-source 130 nm technology and the ETH VLSI 2 implementation flow.

---

## License

Unless stated otherwise in individual file headers:

* hardware RTL and implementation scripts use the **Solderpad Hardware License 0.51**
* software sources use the **Apache License 2.0**

See `LICENSE.md` and the corresponding source-file headers for exact licensing information.
