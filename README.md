# 🤖 ESP32 Line Following Robot

An autonomous line-following robot built using an **ESP32** microcontroller, **IR sensors**, and an **L298N motor driver**. The robot detects a black line on a light-colored surface and follows it by dynamically adjusting motor speed and direction.

---

## 📋 Overview

This project implements a two-sensor (left/right) line-following logic on the ESP32. Based on the combination of IR sensor readings, the robot decides whether to move forward, turn left, turn right, or stop — enabling it to trace a path autonomously without any manual control.

---

## ⚙️ How It Works

1. Two IR sensors (left and right) continuously scan the surface beneath the robot.
2. Each sensor outputs `LOW` when it detects a light (white) surface, and `HIGH` when it detects the line (black).
3. Based on the sensor combination, the robot decides its movement:

| Left Sensor | Right Sensor | Action | Reason |
|:---:|:---:|:---|:---|
| LOW | LOW | Move Forward | Both sensors on white — line is centered |
| HIGH | HIGH | Stop | Both sensors on black — likely at an intersection/end |
| HIGH | LOW | Turn Left | Line drifted to the left |
| LOW | HIGH | Turn Right | Line drifted to the right |

4. Motor speeds are controlled via **PWM** (using the ESP32's `ledcAttach`/`ledcWrite` functions), allowing smooth speed control for both forward motion and turning.

---

## 🛠️ Hardware Components

| Component | Quantity | Purpose |
|---|---|---|
| ESP32 Dev Board | 1 | Main microcontroller |
| IR Sensor Module | 2 | Line detection (left & right) |
| L298N Motor Driver | 1 | Controls motor direction & speed |
| DC Geared Motors | 2 | Drive the wheels |
| Wheels + Caster Wheel | 2 + 1 | Movement and balance |
| Robot Chassis | 1 | Frame to mount all components |
| Battery Pack (7.4V/9V) | 1 | Power supply |
| Jumper Wires | As needed | Connections |

---

## 🔌 Pin Configuration

### IR Sensors
| Signal | ESP32 Pin |
|---|---|
| IR_LEFT | GPIO 35 |
| IR_RIGHT | GPIO 34 |

### L298N Motor Driver
| Signal | ESP32 Pin |
|---|---|
| IN1 | GPIO 18 |
| IN2 | GPIO 19 |
| IN3 | GPIO 25 |
| IN4 | GPIO 14 |
| ENA (Left motor PWM) | GPIO 32 |
| ENB (Right motor PWM) | GPIO 33 |

---

## 💻 Software Details

- **Platform:** Arduino IDE with ESP32 board support
- **ESP32 Arduino Core:** v3.x (uses the newer `ledcAttach()` API instead of the deprecated `ledcSetup()` / `ledcAttachPin()`)
- **PWM Configuration:**
  - Frequency: `1 kHz`
  - Resolution: `8-bit (0–255)`

### Speed Settings (tunable)
```cpp
#define LEFT_SPEED    65   // Forward speed - left motor
#define RIGHT_SPEED   65   // Forward speed - right motor
#define LEFT_TURN     150  // Turning speed - left motor
#define RIGHT_TURN    150  // Turning speed - right motor
```
These values can be tuned depending on your motor characteristics, surface friction, and desired responsiveness.

---

## 🚀 Getting Started

### Prerequisites
- [Arduino IDE](https://www.arduino.cc/en/software) installed
- ESP32 board package added via Board Manager
- USB cable to connect ESP32 to your computer

### Setup Steps
1. Clone or download this repository.
2. Open `line_follower.ino` in the Arduino IDE.
3. Select your ESP32 board and correct COM port under **Tools**.
4. Wire the components according to the [pin configuration](#-pin-configuration) above.
5. Upload the code to the ESP32.
6. Open the Serial Monitor (baud rate `115200`) to view live sensor readings.
7. Place the robot on the line — it will start moving after a 3-second delay.

---

## 📊 Serial Monitor Output

The robot prints real-time sensor states for debugging:
```
LEFT=0  RIGHT=0
LEFT=1  RIGHT=0
LEFT=0  RIGHT=1
>> STOPPED — both on black
```

---

## 🔧 Future Improvements

- [ ] Add more IR sensors (e.g., 5-sensor array) for finer position tracking
- [ ] Implement **PID control** for smoother, faster line following
- [ ] Add obstacle detection using an ultrasonic sensor
- [ ] Bluetooth/WiFi-based remote monitoring using ESP32's built-in connectivity
- [ ] Replace fixed speed logic with analog IR readings for proportional control

---

## 📄 License

This project is open-source and available for personal or educational use.

---

## 🙋 Author

Add your name, GitHub profile link, and contact info here.
