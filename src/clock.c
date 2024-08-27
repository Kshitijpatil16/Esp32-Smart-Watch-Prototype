#include "clock.h"
#include <U8g2lib.h>

extern U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 19800, 60000);

void setupClock() {
  timeClient.begin();
}

void displayClock() {
  timeClient.update();
  
  int hours = timeClient.getHours();
  int minutes = timeClient.getMinutes();
  int seconds = timeClient.getSeconds();
  
  String timeStr;
  if (hours > 12) {
    hours -= 12;
    timeStr = String(hours) + ":" + (minutes < 10 ? "0" : "") + String(minutes) + ":PM";
  } else {
    timeStr = String(hours) + ":" + (minutes < 10 ? "0" : "") + String(minutes) + ":AM";
  }
  
  u8g2.firstPage();
  do {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_profont12_tf);
    u8g2.drawStr(42, 30, timeStr.c_str());
    u8g2.drawStr(34, 44, timeClient.getFormattedDate().c_str());
    u8g2.sendBuffer();
  } while (u8g2.nextPage());
}