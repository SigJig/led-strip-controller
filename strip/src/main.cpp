
#include <Arduino.h>
#include "colors.h"
#include "strip.h"

ColorPin colors[] = { 3, 5, 6, 9 };
RGBWStrip strip(colors);

void setup()
{
  Serial.begin(9600);
}

void transform_motion()
{
  uint64_t time = millis();

  if (time % 10000 == 0)
  {
    auto transform = [&](uint8_t incr_index, uint8_t dec_index)
    {
      uint8_t m = 255;
      for (uint16_t i = 0; i <= m; i++)
      {
        colors[incr_index].set_signal(i);
        colors[dec_index].set_signal(m - i);
        strip.show();

        delayMicroseconds(3500);
      }
    };

    transform(1, 3);
    delay(1);
    transform(3, 1);
  }
}

void rainbow()
{
  static uint16_t hue = 0;

  hue = (hue + 1) % 360;

  strip.set_hsv(hue, 1, 1);
}

void loop()
{
  rainbow();
  //transform_motion();
  /*while (Serial.available())
  {
    int s = Serial.parseInt();
    Serial.println(s);
  }*/

/*
  colors[3].set_signal(130);
  colors[1].set_signal(240);*/


  strip.show();
  delay(10);
}