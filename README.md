# Edge-Computing-Motion-Node
This repository contains the firmware for a local-processing edge node. It interfaces an MPU6050 (6-axis IMU) with an Arduino via the I²C protocol to detect physical impacts and gestures.

## Project Overview
Standard IoT sensors continuously transmit raw, noisy data to the cloud, wasting bandwidth and power. To optimize this, I implemented edge-computing principles directly on the microcontroller:
1. **I²C Hardware Interfacing:** Directly reading specific memory registers (`0x3F`) of the MPU6050.
2. **Digital Signal Processing:** Implemented a lightweight Exponential Moving Average (EMA) filter in C++ to smooth raw Z-axis accelerometer data locally.
3. **Smart Transmission:** The node only transmits an alert state when a calculated acceleration threshold (> 1.5g) is breached, saving IoT gateway bandwidth.

### System Output (Debug Mode)
```text
Raw: 1.02 | Filtered: 1.05
Raw: 1.85 | Filtered: 1.20
Raw: -0.90| Filtered: -0.65
--- IMPACT THRESHOLD EXCEEDED! ---
