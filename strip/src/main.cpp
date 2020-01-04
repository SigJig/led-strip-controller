
#include <Arduino.h>
#include "colors.h"

#define OUT_R 3
#define OUT_G 5
#define OUT_B 6
#define OUT_W 9

double dmap(double x, double in_min, double in_max, double out_min, double out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

ColorPin colors[4] = { OUT_R, OUT_G, OUT_B, OUT_W };

void setup()
{
  Serial.begin(9600);

  // colors[3].set_signal(255);
}

void show_all()
{
  for (uint8_t i = 0; i < 4; i++)
  {
    colors[i].show();
  }
}

void transform_motion()
{
  uint64_t time = millis();

  if (time % 10000 == 0)
  {
    Serial.println("Hit");
    auto transform = [&](uint8_t incr_index, uint8_t dec_index)
    {
      uint8_t m = 255;
      for (uint16_t i = 0; i <= m; i++)
      {
        colors[incr_index].set_signal(i);
        colors[dec_index].set_signal(m - i);
        show_all();

        delayMicroseconds(3500);
      }
      Serial.println("Transformed");
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

  RGB rgb = hsv_rgb(hue, 1, 1);

  colors[0].set_signal(rgb.r);
  colors[1].set_signal(rgb.g);
  colors[2].set_signal(rgb.b);
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


  show_all();
  delay(10);
}