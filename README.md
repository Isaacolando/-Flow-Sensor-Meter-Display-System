# 🔧 LCD Display Feature Branch

![LCD](https://img.shields.io/badge/LCD-I2C-007ACC?style=for-the-badge)
![ESP32](https://img.shields.io/badge/ESP32-000000?style=for-the-badge&logo=espressif&logoColor=white)

**Feature Branch:** `lcd-display`  
**Team Member Contribution** – Embedded Systems Lab

---

## 🎯 What This Branch Implements

This branch is responsible for the **real-time LCD display** functionality of the Flow Sensor Dispensing System.

### Implemented Features:
- ✅ Integrated **I2C 16x2 LCD** using `LiquidCrystal_I2C` library
- ✅ Live display of:
  - **Total Volume Dispensed** (in ml)
  - **Flow Rate** (in L/min)
- ✅ Clean and readable formatting on the LCD
- ✅ Updated display every second during dispensing
- ✅ Proper initialization and backlight control
- ✅ Integration with main dispensing logic (volume & flow rate)

---

## 📋 Files Modified / Added in This Branch

- `flow_sensor.ino` – Added LCD setup, display logic, and real-time updates
- `README.md` – This file (feature branch only)

---

## 🔍 LCD Display Layout (During Operation)

**Line 1:** `Vol: 850 ml`  
**Line 2:** `Flow: 2.8 L/m`

Cost is calculated in the background and shown via Serial Monitor.

---

## 🛠️ How to Test This Feature

1. Switch to this branch
2. Upload `flow_sensor.ino` to ESP32
3. Connect I2C LCD (SDA → GPIO 21, SCL → GPIO 22)
4. Start dispensing using the button
5. Observe real-time updates on the LCD

---

## 📌 Note for Main Branch

This `README.md` file is **only for the `lcd-display` branch** and will **not** be merged into `main`/`master` as per Tutorial 5 requirements.

All other team members' feature branches follow the same pattern.

---

**Contribution by:** [Your Team Member Name]  
**Date:** April 2026  
**Embedded Systems Lab – Flow Sensor Meter & Display System**
