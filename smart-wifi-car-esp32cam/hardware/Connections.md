# 🔌 Wiring Connections

This document explains all the hardware connections between the **ESP32-CAM**, the **ESP32 Dev Board**, the **L293D Motor Driver**, and the **Ultrasonic Sensor**.

---

## 🧠 1. ESP32-CAM Connections (Manual Control + Camera Streaming)

| Component | ESP32-CAM Pin | Description |
|------------|----------------|--------------|
| Motor Driver IN1 | GPIO 13 | Motor A – Direction 1 |
| Motor Driver IN2 | GPIO 15 | Motor A – Direction 2 |
| Motor Driver IN3 | GPIO 14 | Motor B – Direction 1 |
| Motor Driver IN4 | GPIO 2  | Motor B – Direction 2 |
| Motor Driver ENA | GPIO 12 | PWM Speed Control A |
| Motor Driver ENB | GPIO 12 | PWM Speed Control B (shared) |
| TX (UART) | U0T | Data sent to ESP32 Dev (mode communication) |
| RX (UART) | U0R | Data received from ESP32 Dev (obstacle signal) |
| Power | 5 V / GND | From regulated source (phone charger or battery pack) |

---

## 🤖 2. ESP32 Dev Board Connections (Obstacle Detection)

| Component | ESP32 Dev Pin | Description |
|------------|----------------|--------------|
| Ultrasonic Trigger | GPIO 10 (D10) | Sends pulse for distance measurement |
| Ultrasonic Echo | GPIO 11 (D11) | Receives reflected pulse |
| TX (UART) | TX0 | Sends “Obstacle” signal to ESP32-CAM |
| RX (UART) | RX0 | (Optional) Receives commands |
| Power | VIN / GND | From same 5 V battery or USB |

---

## ⚙️ 3. Motor Driver (L293D or L298N)

| Pin | Connected To | Function |
|------|---------------|-----------|
| ENA | GPIO 12 | Left motor speed control |
| IN1 | GPIO 13 | Left motor direction A |
| IN2 | GPIO 15 | Left motor direction B |
| IN3 | GPIO 14 | Right motor direction A |
| IN4 | GPIO 2  | Right motor direction B |
| ENB | GPIO 12 | Right motor speed control (can share same PWM) |
| VCC | 5 V | Power for motor driver logic |
| VCC1 (Motor) | 6–12 V | Motor power (from batteries) |
| GND | Common Ground | Shared ground with ESP32 |

---

## 📡 4. Power Setup
- **Two 3.7 V Li-ion batteries (2000 mAh each)** connected in series → ~7.4 V output.  
- Use a **buck converter** to step down to 5 V if directly powering ESP32 boards.  
- L293D motor driver can handle 6–12 V motors easily.

---

## ⚠️ Important Notes
- Always **common GND** between all modules.  
- Don’t power the ESP32-CAM from the same USB that drives motors — use separate regulated power.  
- Ensure 5 V stable supply to avoid camera brownouts.

---

## 🧩 Quick Overview Diagram (text version)

