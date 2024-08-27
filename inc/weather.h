#ifndef WEATHER_H
#define WEATHER_H

#include <Arduino.h>

void getWeather(String &weather, float &temperature);
void displayWeather(const String &weather, float temperature);

#endif