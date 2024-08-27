#ifndef CLOCK_H
#define CLOCK_H

#include <Arduino.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

void setupClock();
void displayClock();

#endif