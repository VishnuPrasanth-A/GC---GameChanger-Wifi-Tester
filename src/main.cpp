// GC-GC: Game Changer Wi-Fi Pentest Toolkit (Dual Button Version with SD + Network Tools)
// Created by Mr.Vishnu

#include <WiFi.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "esp_wifi.h"

// Display Setup
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET     -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Button Setup
#define BUTTON_SCROLL 17
#define BUTTON_SELECT 18

// SD Card Setup (SPI)
#define SD_CS    5
#define SD_MOSI  23
#define SD_MISO  19
#define SD_SCK   18

// Menu
String menuItems[] = {
  "1. WiFi Scan",
  "2. Connect & Deauth",
  "3. Fake AP",
  "4. Packet Sniff",
  "5. Settings"
};
int selectedItem = 0;
bool lastScrollState = HIGH;
bool lastSelectState = HIGH;
bool showSplashNext = false;

String connectedSSID = "";
bool connectedToWiFi = false;

// ===================== SETUP =====================
void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_SCROLL, INPUT_PULLUP);
  pinMode(BUTTON_SELECT, INPUT_PULLUP);

  Wire.begin(21, 22);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 allocation failed");
    while (1);
  }

  showSplash();
  drawMenu();

  if (!SD.begin(SD_CS)) {
    Serial.println("SD card mount failed");
  } else {
    Serial.println("SD card mounted");
  }
}

// ===================== MAIN LOOP =====================
void loop() {
  bool scrollPressed = digitalRead(BUTTON_SCROLL) == LOW;
  bool selectPressed = digitalRead(BUTTON_SELECT) == LOW;

  if (scrollPressed && lastScrollState == HIGH) {
    if (showSplashNext) {
      showSplash();
      showSplashNext = false;
    } else {
      selectedItem = (selectedItem + 1) % 5;
      drawMenu();
    }
  }

  static unsigned long lastSelectTime = 0;
  if (scrollPressed && (millis() - lastSelectTime < 500)) {
    showSplashNext = true;
  }
  if (selectPressed && lastSelectState == HIGH) {
    executeOption(selectedItem);
    drawMenu();
    lastSelectTime = millis();
  }

  lastScrollState = !scrollPressed;
  lastSelectState = !selectPressed;
  delay(150);
}

// ===================== DISPLAY =====================
void showSplash() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(10, 10);
  display.println("GC");
  display.setTextSize(1);
  display.setCursor(8, 40);
  display.println("Game Changer Toolkit");
  display.display();
  delay(2000);
}

void drawMenu() {
  display.clearDisplay();
  for (int i = 0; i < 5; i++) {
    if (i == selectedItem) display.print("> ");
    else display.print("  ");
    display.println(menuItems[i]);
  }
  display.display();
}

// ===================== MENU EXECUTION =====================
void executeOption(int item) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Running:");
  display.println(menuItems[item]);
  display.display();
  delay(1000);

  switch (item) {
    case 0: wifiScan(); break;
    case 1: connectAndDeauth(); break;
    case 2: createFakeAP(); break;
    case 3: startSniffing(); break;
    case 4: showSettings(); break;
  }
}

// ===================== FEATURES =====================
void wifiScan() {
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  int n = WiFi.scanNetworks();
  display.clearDisplay();
  display.setCursor(0, 0);
  for (int i = 0; i < n && i < 6; i++) {
    display.println(WiFi.SSID(i));
  }
  display.display();
  delay(4000);
}

void connectAndDeauth() {
  File file = SD.open("/wifi_list.txt");
  if (!file) {
    Serial.println("wifi_list.txt missing");
    return;
  }
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  String content = file.readString();
  file.close();

  int n = WiFi.scanNetworks();
  for (int i = 0; i < n; i++) {
    String ssid = WiFi.SSID(i);
    if (content.indexOf(ssid) >= 0) {
      int start = content.indexOf(ssid);
      int pwdStart = content.indexOf("password\":\"", start) + 11;
      int pwdEnd = content.indexOf("\"", pwdStart);
      String password = content.substring(pwdStart, pwdEnd);

      WiFi.begin(ssid.c_str(), password.c_str());
      unsigned long startTime = millis();
      while (WiFi.status() != WL_CONNECTED && millis() - startTime < 10000) delay(500);

      if (WiFi.status() == WL_CONNECTED) {
        connectedSSID = ssid;
        connectedToWiFi = true;
        display.clearDisplay();
        display.setCursor(0, 0);
        display.println("Connected:");
        display.println(ssid);
        display.display();
        delay(2000);
        performDeauth();
        return;
      }
    }
  }
  display.clearDisplay();
  display.println("No match found.");
  display.display();
  delay(2000);
}

void performDeauth() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Deauthing devices...");
  display.display();
  delay(2000);

  // Simulate deauth attack for 2 minutes
  unsigned long start = millis();
  while (millis() - start < 120000) {
    // Here you can implement esp_wifi_80211_tx() with custom deauth packet
    delay(100);
  }
  display.clearDisplay();
  display.println("Devices released");
  display.display();
  delay(1500);
}

void createFakeAP() {
  const char* ssid = "FreeWiFi_GC";
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, "12345678");
  display.clearDisplay();
  display.println("Fake AP running");
  display.println(ssid);
  display.display();
  delay(3000);
}

void snifferCallback(void* buf, wifi_promiscuous_pkt_type_t type) {
  wifi_promiscuous_pkt_t* pkt = (wifi_promiscuous_pkt_t*)buf;
  Serial.printf("[Sniffed] Packet Len: %d\n", pkt->rx_ctrl.sig_len);
}

void startSniffing() {
  WiFi.mode(WIFI_MODE_NULL);
  esp_wifi_set_promiscuous(true);
  esp_wifi_set_promiscuous_rx_cb(&snifferCallback);
  display.clearDisplay();
  display.println("Sniffing packets...");
  display.display();
  delay(10000);
  esp_wifi_set_promiscuous(false);
}

void showSettings() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("[Settings]");
  if (connectedToWiFi) {
    display.print("Connected: ");
    display.println(connectedSSID);
  } else {
    display.println("Not connected");
  }
  display.println("By Mr.Vishnu");
  display.display();
  delay(4000);
}
