#include "pedometer.h"
#include <MPU6050_tockn.h>
#include <U8g2lib.h>

extern MPU6050 mpu6050;
extern U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2;
extern int steps;
extern float distanceInOneStep;
extern float distance;

void displaysteps()
{
  mpu6050.update();

  if (mpu6050.getAccY() > 0.4)
  {
    steps += 1;
    delay(350);
  }

  u8g2.firstPage();
  do
  {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_profont12_tf);
    String stepsstr = String(steps);
    u8g2.drawStr(0, 20, "Steps: ");
    u8g2.drawStr(40, 20, stepsstr.c_str());

    distance = steps * distanceInOneStep / 100;
    String distancestr = String(distance);
    u8g2.drawStr(0, 40, "Distance: ");
    u8g2.drawStr(58, 40, distancestr.c_str());
    u8g2.drawStr(78, 40, " m");

    u8g2.sendBuffer();
  } while (u8g2.nextPage());

  delay(100);
}