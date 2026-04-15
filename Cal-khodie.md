# 🔘 Button Interface Feature Branch

![Button](https://img.shields.io/badge/Feature-Button%20Interface-28A745?style=for-the-badge)
![ESP32](https://img.shields.io/badge/ESP32-000000?style=for-the-badge&logo=espressif&logoColor=white)

**Feature Branch:** `button-interface`  
**Team Member Contribution** – Embedded Systems Lab

---

## 🎯 What This Branch Implements

This branch handles the **Start/Stop button interface** for the Flow Sensor Dispensing System.

### Implemented Features:
- ✅ Added push button on **GPIO 14** for manual control
- ✅ Implemented **debounced button press** detection
- ✅ Toggle functionality to **start and stop dispensing**
- ✅ Control of the pump/relay based on button state
- ✅ Visual feedback on LCD when dispensing starts or stops
- ✅ Proper state management (`dispensing` boolean)
- ✅ Smooth integration with flow sensor and pump control

---

## 📋 Files Modified / Added in This Branch

- `flow_sensor.ino` – Added button pin configuration, interrupt-free debouncing, and toggle logic
- `README.md` – This feature-specific README (only for this branch)

---

## 🔍 Button Behavior

- **Short press**: Toggles dispensing ON/OFF  
- When **ON**: Pump turns ON and system starts measuring flow  
- When **OFF**: Pump turns OFF and flow rate resets to 0  
- LCD shows "Dispensing..." or "Stopped" accordingly

---

## 🛠️ How to Test This Feature

1. Switch to this branch
2. Upload the code to ESP32
3. Connect push button to **GPIO 14** (with pull-up)
4. Press the button to start dispensing
5. Press again to stop
6. Verify pump/relay responds correctly

---

## 📌 Note for Main Branch

This `README.md` file exists **only in the `button-interface` branch** and will **not** be merged into `main`/`master` as per Tutorial 5 requirements.

The main branch will only contain the combined working code without individual feature READMEs.

---

**Contribution by:** [ Cal-khodie /Caleb Njiru]  
**Date:** April 2026  
**Embedded Systems Lab – Flow Sensor Meter & Display System**