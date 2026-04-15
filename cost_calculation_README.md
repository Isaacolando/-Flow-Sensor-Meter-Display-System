# 💰 Cost Calculation Feature Branch

![Cost](https://img.shields.io/badge/Feature-Cost%20Calculation-4CAF50?style=for-the-badge)
![Kenya](https://img.shields.io/badge/KSh-12%20per%2080ml-gold?style=for-the-badge)
![ESP32](https://img.shields.io/badge/ESP32-000000?style=for-the-badge&logo=espressif&logoColor=white)

**Feature Branch:** `cost-calculation`  
**Team Member Contribution** – Embedded Systems Lab

---

## 🎯 What This Branch Implements

This branch handles the **real-time cost calculation** for the liquid being dispensed in the Flow Sensor Dispensing System.

### Implemented Features:
- ✅ Accurate cost calculation based on dispensed volume
- ✅ Cost rate implementation: **12 KSh per 80 ml**
- ✅ Real-time cost update as liquid flows (`0.15 KSh per ml`)
- ✅ Continuous calculation during dispensing
- ✅ Proper floating-point handling for cost value
- ✅ Integration with volume accumulation logic
- ✅ Cost output via Serial Monitor (and prepared for LCD display)

---

## 📋 Files Modified / Added in This Branch

- `flow_sensor.ino` – Added cost calculation logic, rate conversion, and real-time updates
- `README.md` – This feature-specific README (only for this branch)

---

## 💰 Cost Calculation Formula

```math
Cost (KSh) = Total Volume (ml) × 0.15
