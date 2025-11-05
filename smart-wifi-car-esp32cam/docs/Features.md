# 🚗 Smart Wi-Fi Controlled Car with Obstacle Avoidance (ESP32-CAM + ESP32)

This project is a hybrid autonomous + manual control car that uses two ESP32 modules:
- **ESP32-CAM** → Handles Wi-Fi control, camera streaming, and manual mode.
- **ESP32 Dev Board** → Manages ultrasonic sensor–based obstacle avoidance and auto-driving logic.

---

## ✨ Features

### 🧠 Hybrid Operation Mode
- **Manual Mode:** Control the car via a web interface using Wi-Fi (forward, backward, left, right, stop).
- **Automatic Mode:** The car autonomously avoids obstacles using an ultrasonic sensor.

### 📸 Live Camera Feed
- Real-time video stream from the ESP32-CAM via a local web server.
- Useful for FPV (first-person view) navigation.

### 🚧 Smart Obstacle Detection
- Ultrasonic sensor (HC-SR04) detects obstacles in front of the car.
- The car automatically stops and takes an alternate path if the distance is below a safe threshold.

### 🔄 Automatic Mode Switching
- The car switches between Auto and Manual modes dynamically.
- (In future versions: add a button or wireless trigger.)

### ⚙️ Dual ESP32 Architecture
- The **ESP32-CAM** handles Wi-Fi and video.
- The **ESP32 Dev Board** runs the ultrasonic logic and motor control for obstacle avoidance.

### 🔋 Power Efficient & Modular
- Runs on two 3.7 V Li-ion batteries (2000 mAh each) connected in series.
- Easy to scale and modify for future enhancements like GPS, solar, or line-following.

---

## 🛠️ Tech Stack
- **Microcontrollers:** ESP32-CAM & ESP32 Dev Board  
- **Motor Driver:** L293D / L298N Dual H-Bridge  
- **Sensor:** HC-SR04 Ultrasonic Distance Sensor  
- **Communication:** UART (TX/RX) between both boards  
- **Programming:** Arduino IDE  
- **Interface:** Web-based control panel with live camera stream  

---

## 🚀 Future Upgrades
- Add battery voltage monitoring  
- Integrate solar charging module  
- Implement line-following or object-tracking via camera  
- Add mobile-app based control (via Blynk or Flutter)
