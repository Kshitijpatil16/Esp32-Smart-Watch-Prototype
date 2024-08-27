#include "weather.h"
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <U8g2lib.h>

extern U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2;
extern const char *host;
extern const char *apiKey;
extern const char *city;

void getWeather(String &weather, float &temperature)
{
  HTTPClient http;

  String apiUrl = "http://api.openweathermap.org/data/2.5/weather?q=";
  apiUrl += city;
  apiUrl += "&appid=";
  apiUrl += apiKey;

  http.begin(apiUrl);

  int httpCode = http.GET();

  if (httpCode > 0)
  {
    String payload = http.getString();
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, payload);

    weather = doc["weather"][0]["main"].as<String>();
    temperature = doc["main"]["temp"].as<float>() - 273.15;
  }

  http.end();
}

void displayWeather(const String &weather, float temperature)
{
  u8g2.firstPage();
  do
  {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_profont12_tf);
    u8g2.setCursor(2, 25);
    u8g2.print("Weather: ");
    u8g2.println(weather);
    u8g2.setCursor(2, 45);
    u8g2.print("Temperature: ");
    u8g2.print(temperature);
    u8g2.print(" °C");
  } while (u8g2.nextPage());
}