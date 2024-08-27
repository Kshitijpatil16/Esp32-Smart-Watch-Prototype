#include "smart_attendance.h"
#include <MFRC522.h>
#include <HTTPClient.h>
#include <U8g2lib.h>
#include <NTPClient.h>

extern MFRC522 mfrc522;
extern U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2;
extern NTPClient timeClient;
extern String arr_days[];
extern String t;
extern String d;
extern String date;
extern String date_time;
extern String payload;

void displaySmartAttendance()
{
  static bool isNewCardPresent = false;
  static bool isCardRead = false;
  static unsigned long previousMillis = 0;

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 500)
  {
    previousMillis = currentMillis;
    isNewCardPresent = mfrc522.PICC_IsNewCardPresent();
    isCardRead = mfrc522.PICC_ReadCardSerial();
  }

  if (isNewCardPresent && isCardRead)
  {
    String id = "";
    for (byte i = 0; i < mfrc522.uid.size; i++)
    {
      id.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));
      id.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    mfrc522.PICC_HaltA();

    HTTPClient http;
    http.begin("http://192.168.179.145/attendance/insert.php?date=" + String(date) + "&time=" + String(t) + "&rf=" + String(id));

    int httpCode = http.GET();
    if (httpCode > 0)
    {
      payload = http.getString();
    }
    http.end();

    u8g2.firstPage();
    do
    {
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_profont12_tf);
      u8g2.drawStr(0, 20, "OK");
      u8g2.drawStr(0, 40, "Done..");
      u8g2.drawStr(0, 60, "Attendance Recorded");
      u8g2.sendBuffer();
    } while (u8g2.nextPage());

    delay(2000);
  }

  timeClient.update();
  int hh = timeClient.getHours();
  int mm = timeClient.getMinutes();
  int ss = timeClient.getSeconds();
  if (hh > 12)
  {
    hh -= 12;
    t = String(hh) + ":" + mm + ":PM";
  }
  else
  {
    t = String(hh) + ":" + mm + ":AM";
  }

  int day = timeClient.getDay();
  d = arr_days[day];
  date_time = timeClient.getFormattedTime();
  int index_date = date_time.indexOf("T");
  date = date_time.substring(0, index_date);

  u8g2.firstPage();
  do
  {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_profont12_tf);
    u8g2.drawStr(0, 20, "Smart Attendance");
    u8g2.drawStr(0, 40, "Time:");
    u8g2.drawStr(35, 40, t.c_str());
    u8g2.drawStr(0, 60, "Date:");
    u8g2.drawStr(35, 60, date.c_str());
    u8g2.sendBuffer();
  } while (u8g2.nextPage());

  delay(1000);
}