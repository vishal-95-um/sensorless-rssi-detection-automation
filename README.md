# ESP32 RSSI-Based Human Detection

This project uses an ESP32 to detect human presence based on RSSI (Received Signal Strength Indicator) fluctuations from a known WiFi SSID. When a significant drop in signal is detected, it is interpreted as human presence, and a bulb (or any appliance) connected through a relay is turned on for 5 seconds.

![photo_6285095360049302508_y](https://github.com/user-attachments/assets/bc584437-1a9d-455e-86de-aee2a9915202)


## 🧠 Core Concept

- The ESP32 scans for a specific WiFi network.
- RSSI values are collected in a circular buffer (size = 3).
- If the difference between the latest and previous RSSI reading exceeds a threshold (`>8dBm`), human presence is assumed.
- A relay is activated via GPIO22 for 5 seconds when presence is detected.

## ⚙️ Hardware Required

- ESP32 Dev Board
- 1-channel 5V Relay Module (I had 2 channel so I used that)
- Bulb or load device
- Jumper wires
- Breadboard


## 📋 Circuit Connection

| ESP32 Pin | Relay Module Pin |
|-----------|------------------|
| GPIO22    | IN               |
| GND       | GND              |
| 5V        | VCC              |

- The bulb is connected to the relay's NO (Normally Open) and COM terminals.


## 📝 Code Overview

- `WiFi.scanNetworks()` is used to measure RSSI.
- Buffer of 3 RSSI values is maintained.
- Comparison between current and avg RSSI is done.
- `digitalWrite(bulb_pin, LOW)` turns the relay ON (depending on relay logic).
- `millis()` is used to control how long the bulb stays ON.


## 🚀 Getting Started

1. Install the following libraries in Arduino IDE:
   - `WiFi.h` (built-in for ESP32)
2. Flash the code to your ESP32.
3. Change `const char* ssid = "YourWiFi";` and `const char* password = "YourPassword";`.


## 🛠 Future Improvements

- Add HTTP/JSON-based logging to Node-RED or cloud.
- Use signal smoothing/filters (e.g., Kalman filter).
- Use multiple WiFi SSIDs or access points for better detection.
- Optional: Add MQTT/ThingSpeak for IoT integration.


## 🧠 Author Notes

- This code was written and tested in a real-world home setup.
- `delay(500)` is used to scan twice every second.
- Keep relay logic in mind: LOW = ON for most modules.



