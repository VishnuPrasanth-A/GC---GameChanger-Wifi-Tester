Here’s your updated and **GitHub-ready `README.md`** file, with proper `##` section formatting, bullet alignment, code blocks, and markdown best practices. This version is polished, clean, and matches standard open-source presentation guidelines:

---

````markdown
# GC---GameChanger-WiFi-Tester

The **GC Toolkit (Game Changer)** is an advanced, self-contained **Wi-Fi penetration testing and network diagnostic tool** powered by the **ESP32 board**.  
It features a clean **OLED user interface** with **dual-button control** and powerful capabilities — ideal for cybersecurity learners, ethical hackers, and network testers.

---

## ✨ Features

- 📡 **WiFi Scanner** – View nearby SSIDs
- 🔐 **Auto Connect & Deauth** – Connect to saved networks and perform timed deauthentication attacks
- 🌐 **Fake AP + Captive Portal** – Set up phishing-style hotspots for training/testing
- 📁 **SD Card Integration** – Read stored SSID/passwords from `wifi_list.txt`
- 🛰 **Packet Sniffer** – Capture raw 802.11 packets in monitor mode
- 📲 **BLE Mode** – Trigger actions via Bluetooth
- 💻 **Web Dashboard** – View live logs/status in your browser
- 🧠 **OLED UI** – Scroll/select navigation using dual push buttons

---

## 📦 Hardware Required

| Component           | Description                  |
|--------------------|------------------------------|
| ESP32 Dev Board     | 30/38-pin with WiFi & BLE     |
| OLED Display        | SSD1306 128x64 (I2C)          |
| Push Buttons × 2    | Scroll & Select navigation    |
| SD Card Module      | SPI-based (FAT32-formatted)   |
| microSD Card        | 1GB or more, FAT32 format     |
| Jumper Wires        | Male–Female recommended       |
| Power Source        | USB or 5V Power Bank          |

---

## 🔌 Wiring Diagram

| Component     | ESP32 GPIO Pin |
|---------------|----------------|
| OLED SDA      | GPIO21         |
| OLED SCL      | GPIO22         |
| Scroll Button | GPIO17         |
| Select Button | GPIO18         |
| SD CS         | GPIO5          |
| SD MOSI       | GPIO23         |
| SD MISO       | GPIO19         |
| SD CLK (SCK)  | GPIO18         |

> ⚠️ Ensure your SD card module supports **3.3V logic** or use level shifters if needed.

---

## 🗃️ SD Card Setup

1. Format the card as **FAT32**
2. Place a file named `wifi_list.txt` in the root directory
3. Example content:

```json
[
  { "ssid": "MyHomeWiFi", "password": "mypassword123" },
  { "ssid": "CafeNet", "password": "coffeetime" }
]
````

---

## 🧠 Software Stack

* **PlatformIO** + **Arduino Framework**
* Core Libraries:

  * `Adafruit SSD1306`
  * `Adafruit GFX`
  * `NimBLE-Arduino`
  * `ESPAsyncWebServer`
  * `ESPAsyncTCP`
  * `SD` / `SPI`
  * `WiFi` / `esp_wifi`

---

## ⚙️ PlatformIO Configuration

Your `platformio.ini` should look like this:

```ini
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
```

---

## 🚀 Setup Instructions

1. **Clone this repository**

   ```bash
   git clone https://github.com/<your-username>/GC-Wifi-Tester.git
   cd GC-Wifi-Tester
   ```

2. **Open in VSCode with PlatformIO extension**

3. **Prepare SD card**

   * Format as FAT32
   * Add `wifi_list.txt` with network credentials

4. **Connect ESP32 via USB**

5. **Upload code**

   * In VSCode: press `Upload` in PlatformIO
   * Or via terminal:

     ```bash
     pio run --target upload
     ```

6. **Monitor Serial**

   ```bash
   pio device monitor
   ```

7. **Power Off-PC**

   * Disconnect from laptop and power using any 5V power bank
   * Device runs standalone

---

## 🕵️ Legal Disclaimer

> ⚠️ This project is intended **only** for **educational and authorized penetration testing**.

* Unauthorized access or attacks on Wi-Fi networks **without consent** is **illegal** and subject to criminal charges under cyber law.

---

## ❤️ About

This project is created with ❤️ by **Mr. Vishnu**
For ethical hackers, security learners, and pentest researchers.

> 100% Open Source — share knowledge, not exploits!

---
