# 🚀 ESP32 Flow Sensor Dispensing System

![ESP32](https://img.shields.io/badge/ESP32-000000?style=for-the-badge&logo=espressif&logoColor=white)
![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Arduino IDE](https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![Embedded Systems](https://img.shields.io/badge/Lab-Embedded%20Systems-blueviolet?style=for-the-badge)

**Embedded Systems Lab: Flow Sensor Meter & Display System**  
**Real-time Liquid Dispensing Machine with Cost Calculation**

---

## 🎯 Project Objective

This system uses an **ESP32 microcontroller** to:
- Measure liquid flow using a **YF-S201 Hall-effect flow sensor**
- Control a pump/valve for dispensing
- Display **real-time** values on an I2C LCD:
  - Total Volume Dispensed (ml)
  - Flow Rate (L/min)
  - Total Cost in Kenyan Shillings (KSh)
- Automatically stop dispensing at **≥ 850 ml**
- Calculate cost at **12 KSh per 80 ml** (i.e., **0.15 KSh per ml**)

---

## ✨ Key Features

- ✅ Pulse counting from flow sensor using interrupt (GPIO 27)
- ✅ Real-time volume, flow rate & cost calculation
- ✅ Push button (GPIO 14) to start/stop dispensing
- ✅ Relay control for pump/valve (GPIO 26)
- ✅ Auto-stop when target of **850 ml** is reached
- ✅ Live updates on **I2C 16x2 LCD**
- ✅ Detailed output via Serial Monitor
- ✅ Fully meets all Embedded Systems Lab requirements

---

## 🛠️ Hardware Used

| Component                  | ESP32 Pin      | Role |
|---------------------------|----------------|------|
| YF-S201 Flow Sensor       | GPIO 27        | Pulse input (interrupt) |
| I2C 16×2 LCD              | SDA=21, SCL=22 | Real-time display |
| Start/Stop Button         | GPIO 14        | Toggle dispensing |
| Relay / Pump / Valve      | GPIO 26        | Control liquid flow |

---

## 💰 Cost Calculation

**Rate:** 12 Kenyan Shillings per 80 ml  
**Formula:**  
```math
Cost (KSh) = Total Volume (ml) × 0.15
