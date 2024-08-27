#include "temperature.h"
#include <U8g2lib.h>

extern U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2;
extern const float referenceVoltage;

void displayTemperature()
{
  int sensorValue = analogRead(32);
  float voltage = (sensorValue * referenceVoltage) / 4095.0;
  float temperatureC = 50 - (voltage * 100.0);
  float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;

  u8g2.firstPage();
  do
  {
    u8g2.setCursor(0, 15);
    u8g2.print("Temperature:");
    u8g2.setCursor(0, 35);
    if (temperatureC >= 0)
    {
      u8g2.print(" ");
    }
    u8g2.print(temperatureC);
    u8g2.print(" C");
    u8g2.setCursor(0, 55);
    if (temperatureF >= 0)
    {
      u8g2.print(" ");
    }
    u8g2.print(temperatureF);
    u8g2.print(" F");
  } while (u8g2.nextPage());

  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.print(" C / ");
  Serial.print(temperatureF);
  Serial.println(" F");
}