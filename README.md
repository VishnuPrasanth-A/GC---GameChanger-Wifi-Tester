# GC---GameChanger-Wifi-Tester
The GC- Toolkit (Game Changer) is an advanced, self-contained Wi-Fi penetration testing and network diagnostic tool powered by the ESP32 board.  It features a clean OLED user interface with dual-button control and multiple powerful capabilities that make it perfect for cybersecurity students, ethical hackers, and network testers.

## ✨ Features

- 📡 **WiFi Scanner** — View nearby SSIDs
- 🔐 **Auto Connect & Deauth** — Connect to known networks and perform timed deauthentication attacks
- 🌐 **Fake AP + Captive Portal** — Setup phishing-style hotspots for testing
- 📁 **SD Card Integration** — Reads a list of stored SSIDs/passwords from `wifi_list.txt`
- 🛰 **Packet Sniffer** — Capture raw 802.11 packets
- 📲 **BLE Mode** — Control or trigger actions via Bluetooth
- 💻 **Web Dashboard** — View live status over the browser
- 🧠 **OLED UI** — Navigate menus with scroll/select buttons

---

## 📦 Hardware Required

| Component           | Description                |
|--------------------|----------------------------|
| ESP32 Dev Module   | 30 or 38-pin with Wi-Fi/BLE |
| OLED Display       | SSD1306, 128x64 (I2C)       |
| 2x Push Buttons    | Scroll & Select navigation |
| SD Card Module     | SPI interface (FAT32 card) |
| Jumper Wires       | Male-Female recommended    |
| Power Bank / USB   | 5V input (no PC needed)     |

### 🧰 Wiring Summary

| Part      | ESP32 GPIO |
|-----------|------------|
| OLED SDA  | GPIO21     |
| OLED SCL  | GPIO22     |
| Button 1  | GPIO17     |
| Button 2  | GPIO18     |
| SD CS     | GPIO5      |
| SD MOSI   | GPIO23     |
| SD MISO   | GPIO19     |
| SD SCK    | GPIO18     |

---

## 🗃️ SD Card Setup

1. Format card as **FAT32**
2. Create `wifi_list.txt` in root
3. Example:

```json
[
  {"ssid": "MyHomeWiFi", "password": "mypassword123"},
  {"ssid": "CafeNet", "password": "coffeetime"}
]
🧠 Software Stack
PlatformIO + Arduino Framework

Libraries:

Adafruit SSD1306 / GFX

NimBLE-Arduino

ESPAsyncWebServer

ESPAsyncTCP

SD / SPI

WiFi / esp_wifi

⚙️ PlatformIO Configuration
ini
Copy
Edit
[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino
monitor_speed = 115200

lib_deps =
  adafruit/Adafruit SSD1306 @ ^2.5.15
  adafruit/Adafruit GFX Library @ ^1.12.1
  NimBLE-Arduino
  ESP Async WebServer
  ESPAsyncTCP
🚀 Setup Instructions
Clone this repo

Open in VSCode with PlatformIO

Insert SD card with wifi_list.txt

Connect ESP32 via USB

Hit Upload

Use serial monitor at 115200 to debug

Or power using USB power bank — runs standalone

🕵️ Legal Disclaimer
This toolkit is intended for educational and authorized penetration testing purposes only.

❗ Unauthorized access or attacks on Wi-Fi networks without permission is illegal and punishable under law.

❤️ About
This project is made with love for learners, cybersecurity enthusiasts, and ethical hackers.

Developed by Mr. Vishnu
100% open-source for ethical research and education.
