#include "ir_sensor.h"

extern const int IR_PIN;
extern const int LED_PIN;
extern int currentPage;

bool objectDetected = false;
bool ledState = false;

void setupIRSensor() {
  // No additional setup needed as pins are already configured in main.cpp
}

void checkIRSensor() {
  int irValue = digitalRead(IR_PIN);
  
  if (irValue == LOW && !objectDetected) {
    objectDetected = true;
    currentPage++;
    if (currentPage == 5) {
      currentPage = 0;
    }
    digitalWrite(LED_PIN, HIGH);
  } else if (irValue == HIGH && objectDetected) {
    objectDetected = false;
    digitalWrite(LED_PIN, LOW);
  }
  
  delay(100); // Debounce delay
}