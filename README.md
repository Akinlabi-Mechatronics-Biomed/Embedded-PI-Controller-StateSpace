# Real-Time Switched-Mode Power Converter Emulator

## Overview
This repository contains the core embedded control and mathematical plant models for a real-time Switched-Mode Power Converter (H-bridge/Inverter) emulator. It is designed to test embedded control software without requiring physical hardware loads.

The code is optimized for deployment on high-performance processors like Zynq SoC or STM32 Nucleo boards, running at a 50 kHz sampling rate.

## Key Features
* **Modular PI Controller (`controller.c`)**: Implements a re-entrant Proportional-Integral (PI) controller in C.
* **Integral Anti-Windup**: Includes saturation clamping to prevent accumulator overflow during aggressive load changes, ensuring system stability.
* **Discrete State-Space Model (`model.c`)**: Translates continuous continuous-time converter dynamics into a 6th-order discrete-time state-space matrix model ($x_{k+1} = Ax_k + Bu_k$).
* **Real-Time Execution**: Hardcoded, flattened arrays for floating-point matrix multiplication to ensure $O(n^2)$ execution within strict microsecond timing constraints.

## Application
This software acts as the "Plant" in a Hardware-in-the-Loop (HIL) simulation. By inputting PWM signals as `u_in`, the state-space model updates the capacitor voltages and inductor currents, outputting the simulated load voltage via `Model_GetOutputVoltage()`.
