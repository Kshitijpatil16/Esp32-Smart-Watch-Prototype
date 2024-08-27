#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>
#include <U8g2lib.h>
#include "clock.h"
#include "ir_sensor.h"
#include "temperature.h"
#include "weather.h"
#include "smart_attendance.h"
#include "pedometer.h"

// Pin definitions
const int I2C_SDA_PIN = 21;
const int I2C_SCL_PIN = 22;
const int LED_PIN = 12;
const int IR_PIN = 34;

// OLED display setup
U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE, I2C_SCL_PIN, I2C_SDA_PIN);

// Wi-Fi credentials
const char *ssid = "Kshitij";
const char *password = "ksp16b22";

int currentPage = 0;

void setup() {
  Serial.begin(921600);
  
  u8g2.begin();
  Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);
  
  pinMode(LED_PIN, OUTPUT);
  pinMode(IR_PIN, INPUT);
  
  connectToWiFi();
  setupClock();
  setupIRSensor();
  setupTemperature();
  setupWeather();
  setupSmartAttendance();
  setupPedometer();
  
  displayWelcomeScreen();
}

void loop() {
  checkIRSensor();
  
  switch(currentPage) {
    case 0:
      displayClock();
      break;
    case 1:
      displayWeather();
      break;
    case 2:
      displayTemperature();
      break;
    case 3:
      displayPedometer();
      break;
    case 4:
      displaySmartAttendance();
      break;
  }
}

void connectToWiFi() {
  Serial.println("Connecting to Wi-Fi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi");
}

void displayWelcomeScreen() {
  u8g2.firstPage();
  do {
    u8g2.clearBuffer();
    u8g2.setDrawColor(1);
    u8g2.setFont(u8g2_font_profont12_tf);
    u8g2.drawFrame(20, 10, 88, 44);
    u8g2.drawStr(20, 34, "Hello, Kshitij!");
    u8g2.sendBuffer();
  } while (u8g2.nextPage());
  delay(2000);
}