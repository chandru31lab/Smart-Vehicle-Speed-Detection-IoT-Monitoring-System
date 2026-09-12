# 🚗 Smart Vehicle Speed Detection & IoT Monitoring Systemr

### ESP32-Based Vehicle Speed Detection & Blynk IoT Monitoring

> A dual-IR sensor based vehicle speed detection system using ESP32 to measure vehicle speed, detect overspeeding, count vehicles, and display real-time data on an I2C LCD and Blynk dashboard.

[![Platform](https://img.shields.io/badge/Platform-ESP32-blue)](https://www.espressif.com/)
[![Embedded](https://img.shields.io/badge/Embedded-C%20%7C%20C%2B%2B-red)](https://www.arduino.cc/)
[![IoT](https://img.shields.io/badge/IoT-Blynk-purple)](https://blynk.io/)
[![Sensors](https://img.shields.io/badge/Sensors-Dual%20IR-green)]()
[![Display](https://img.shields.io/badge/Display-I2C%20LCD-orange)]()

---

## 📌 Overview

The system uses **two IR sensors placed at a fixed distance** to measure the time taken by a vehicle to travel between them.

```text
Vehicle
   ↓
IR Sensor 1 → Start Timer
   ↓
 Fixed Distance
   ↓
IR Sensor 2 → Stop Timer
   ↓
ESP32 → Calculate Speed
   ├── I2C LCD
   └── Blynk Dashboard
```

### Speed Calculation

```text
Speed = Distance / Time
```

The ESP32 uses `micros()` for high-resolution timing and calculates speed in **m/s**.

---

## 🚨 Features

- 🚗 Real-time vehicle speed measurement
- ⚡ Overspeed detection
- 🔢 Vehicle counting
- 📟 16×2 I2C LCD display
- 📱 Blynk IoT dashboard
- 📡 ESP32 Wi-Fi connectivity

---

## 📱 Blynk Dashboard

| Virtual Pin | Data |
|-------------|------|
| **V0** | Speed (m/s) |
| **V1** | Total Vehicles Crossed |
| **V2** | Overspeeding Vehicles |

Example:

```text
Speed
2.86 m/s

Total Vehicles Crossed
22

No. of Overspeeding Vehicles
14
```

---

## 🔌 Hardware

| Component | ESP32 Pin |
|-----------|-----------|
| IR Sensor 1 | GPIO 4 |
| IR Sensor 2 | GPIO 5 |
| LCD SDA | GPIO 21 |
| LCD SCL | GPIO 22 |

### Components

- ESP32
- 2 × IR Sensors
- 16×2 I2C LCD

---

## 💻 Technologies

- C / C++
- ESP32
- Arduino IDE
- GPIO
- I2C
- Wi-Fi
- Blynk IoT

---

## 🔄 Working

```text
Sensor 1 Detection
        ↓
   Start Timer
        ↓
Sensor 2 Detection
        ↓
    Stop Timer
        ↓
  Calculate Speed
        ↓
 ┌──────┴──────┐
 ↓             ↓
LCD           Blynk
 ↓             ↓
Speed       Dashboard
        ↓
Check Overspeed
        ↓
Update Counters
```

---

## ⚙️ Configuration

### Sensor Distance

```cpp
#define SENSOR_DISTANCE_CM 10.0
```

### Overspeed Threshold

```cpp
#define OVERSPEED_LIMIT 5.0
```

Example:

```text
5 m/s = 18 km/h
```

---

## 🚀 Future Improvements

- Automatic Number Plate Recognition (ANPR)
- Camera-based vehicle detection
- GPS tracking
- Cloud data logging
- Historical speed analytics
- Mobile notifications
- Multi-lane monitoring

---

## 📌 Project Summary

> An ESP32-based smart vehicle speed detection system integrating dual IR sensors, real-time speed calculation, overspeed detection, vehicle counting, I2C LCD display, and Blynk IoT monitoring.

---

## 👤 Author

**Ramachandru**  
B.Tech Electronics & Communication Engineering

**Embedded Systems | IoT | Electronics**
