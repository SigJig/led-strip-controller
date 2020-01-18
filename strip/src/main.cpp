
#include <Arduino.h>
#include <SPI.h>
#include <WiFiNINA.h>

#include "../config.h"

#define BAUD_RATE 9600

const char* ssid = NETWORK_SSID;
const char* password = NETWORK_PASS;

#include "strip.h"

#define NUM_STRIPS 2

ColorPin s1[] = {6, 8, 9, 100};
ColorPin s2[] = {12, 13, 14, 100};

RGBWStrip strips[NUM_STRIPS] = {s1, s2};

void setup()
{
  Serial.begin(BAUD_RATE);

  Serial.println("Connecting to Wifi");
  WiFi.begin(ssid, password);

  for (int time = millis(); WiFi.status() != WL_CONNECTED; time = millis())
  {
    if ((time % 2000) == 0) Serial.println("Connecting...");
  }

  Serial.println("Wifi connection established");
  
  for (uint8_t i = 0; i < NUM_STRIPS; i++) strips[i].set_rgb({255, 0, 0});
}

void loop()
{
  if (millis() % 10000 == 0)
  {
    auto gr = [&](RGBW rgbw)
    {
      for (uint8_t i = 0; i < NUM_STRIPS; i++)
      {
        auto strip = strips[i];

        strip.commit_rgbw(rgbw, 1);
      }
    };
    gr({255, 170, 0, 0});
    delay(1000);
    gr({170, 0, 255, 0});
  }
  
}