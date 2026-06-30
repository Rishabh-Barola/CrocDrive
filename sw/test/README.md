# CrocDrive Software and RTL Test Guide

This directory contains the C firmware tests used to verify **CrocDrive**, a Croc SoC extension with an Advanced Motor-Control Peripheral (AMCP). AMCP adds:

- hardware PWM generation,
- quadrature encoder (QEN) decoding,
- GPIO0 alternate-function PWM routing,
- memory-mapped control/status registers in the Croc user domain.

The tests in this directory are intended to be run on the full Croc SoC Verilator simulation. The standalone RTL unit testbenches for the PWM and QEN cores are located under `rtl/user_domain/tb/`.

---

## 1. Recommended quick regression

From the repository root, run:

```bash
./run_final_verilator_tests.sh
