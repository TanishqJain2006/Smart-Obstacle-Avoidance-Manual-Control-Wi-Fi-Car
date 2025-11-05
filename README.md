# 🚗 Smart Wi-Fi Controlled Car (ESP32 + ESP32-CAM)

This project is a **Smart Wi-Fi Controlled Car** built using an **ESP32-CAM** and a secondary **ESP32 board**.  
It can operate in **two modes**:
- 🤖 **Automatic Mode:** Uses an ultrasonic sensor to detect and avoid obstacles.
- 🕹️ **Manual Mode:** Controlled via a Wi-Fi-based web interface with live video streaming.

The project combines **IoT + Robotics + Embedded Systems**, making it an excellent Electrical & Electronics Engineering project.

---

## 🧠 Features

✅ Live camera streaming via ESP32-CAM  
✅ Web-based control interface (Forward, Backward, Left, Right, Stop)  
✅ Automatic obstacle avoidance using ultrasonic sensor  
✅ Dual-ESP32 communication (Serial-based)  
✅ Smooth switching between Auto and Manual modes  
✅ L298N motor driver for motor control  
✅ Powered by dual 3.7 V Li-ion batteries  

---

## 🧩 Components Used

| Component | Quantity | Description |
|------------|-----------|-------------|
| ESP32-CAM (AI Thinker) | 1 | Provides camera feed and Wi-Fi control |
| ESP32 Devkit V1 | 1 | Handles ultrasonic sensing and auto mode |
| Ultrasonic Sensor (HC-SR04) | 1 | Detects obstacles |
| L298N Motor Driver | 1 | Controls DC motors |
| DC Motors | 2 | For left and right wheels |
| Li-ion Batteries (3.7 V, 2000 mAh) | 2 | Power source |
| Jumper Wires | — | Circuit connections |

---

## ⚡ Wiring Connections

### 🧭 ESP32-CAM (Main Board – Manual Control + Camera)

| Function | Pin | Connected To |
|-----------|-----|--------------|
| Motor IN1 | GPIO 13 | L298N IN1 |
| Motor IN2 | GPIO 15 | L298N IN2 |
| Motor IN3 | GPIO 14 | L298N IN3 |
| Motor IN4 | GPIO 2 | L298N IN4 |
| ENA / ENB | GPIO 12 | L298N Enable |
| RX (U0R) | GPIO 3 | TX (GPIO 17) of Second ESP32 |
| 5 V | 5 V | Battery Output |
| GND | GND | Common Ground |

---

### 🧠 ESP32 Devkit V1 (Auto Mode + Obstacle Detection)

| Function | Pin | Connected To |
|-----------|-----|--------------|
| Trigger | GPIO 5 | Ultrasonic Trig |
| Echo | GPIO 18 | Ultrasonic Echo |
| TX | GPIO 17 | RX (GPIO 3) of ESP32-CAM |
| 5 V | 5 V | Battery Output |
| GND | GND | Common Ground |

---

## 💻 How It Works

1. **ESP32-CAM** creates a Wi-Fi network and hosts a webpage with:
   - Live camera feed  
   - Movement buttons (↑ Forward ↓ Backward ← Left → Right ■ Stop)

2. **Second ESP32** continuously monitors the distance using the ultrasonic sensor.  
   If an obstacle is detected (e.g. distance < 20 cm), it sends an `"OBSTACLE"` message to the ESP32-CAM through the serial connection.

3. The **ESP32-CAM** immediately stops the motors upon receiving `"OBSTACLE"`.

4. You can toggle between **Auto Mode** (self-driving) and **Manual Mode** (controlled from webpage).

---

## 🌐 Webpage Interface

The ESP32-CAM hosts a webpage accessible through your browser.

Example: http://192.168.x.xxx

*(The IP address will be shown in the Arduino Serial Monitor after uploading the code.)*

The webpage includes:
- 📸 Live Camera Stream  
- 🕹️ Movement Buttons (Forward, Backward, Left, Right, Stop)  
- 🔁 Mode Switching between Auto and Manual  

---

## 🧰 Setup Instructions

1. **Install ESP32 Board Support:**
   - In Arduino IDE → Preferences →  
     Add this URL in *Additional Boards Manager URLs:*  
     ```
     https://dl.espressif.com/dl/package_esp32_index.json
     ```
   - Then go to *Tools → Board → Boards Manager → Search "ESP32" → Install.*

2. **Select Board for ESP32-CAM:**
   - *Tools → Board → AI Thinker ESP32-CAM*  
   - Upload `esp32_cam_car.ino`

3. **Select Board for ESP32 Controller:**
   - *Tools → Board → ESP32 Dev Module*  
   - Upload `esp32_obstacle_auto.ino`

4. **Open Serial Monitor** after uploading ESP32-CAM code → note the IP address.  
5. Connect your phone or laptop to the same Wi-Fi → open that IP in your browser.  
6. Control your car live from anywhere on the same network!

---

## 🧾 Folder Structure
```bash
smart-wifi-car-esp32cam/
├── firmware/
│ ├── esp32-cam/
│ │ ├── esp32_cam_car.ino
│ │ └── camera_pins.h
│ └── esp32-obstacle/
│ └── esp32_obstacle_auto.ino
├── hardware/
│ ├── wiring-diagram.png
│ └── connections.md
├── docs/
│ ├── flowchart.png
│ ├── demo-video-link.txt
│ └── features.md
└── images/
├── car_front_view.jpg
├── car_top_view.jpg
├── webpage_ui.png
└── working_demo.png
```

---

## 🧪 Future Enhancements

- Add speed control using PWM signals  
- Implement battery voltage monitoring  
- Add solar charging system  
- Add voice control (Google Assistant or Alexa integration)  

---

## 📜 License
This project is open source and available under the **MIT License**.

---

## 💬 Description (for GitHub)
> Smart Wi-Fi Controlled Car using ESP32-CAM and Ultrasonic Sensor with Manual and Auto Modes.


