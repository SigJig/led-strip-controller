
#include <Arduino.h>
#include <SPI.h>
#include <WiFiNINA.h>

#include "../config.h"

#define BAUD_RATE 9600

const char* ssid = NETWORK_SSID;
const char* password = NETWORK_PASS;

#include "strip.h"

#define NUM_STRIPS 2

ColorPin s1[] = {6, 8, 9};
ColorPin s2[] = {12, 13, 14};

RGBStrip strips[NUM_STRIPS] = {s1, s2};

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
  
  for (uint8_t i = 0; i < NUM_STRIPS; i++) {
    auto strip = strips[i];
  
    strip.set_rgb({255, 255, 255});
  }
}

void loop()
{
  for (uint8_t i = 0; i < NUM_STRIPS; i++) 
  {
    strips[i].show();
  }

#ifdef no
  if (millis() % 2000 == 0)
  {
    Serial.println("Initializing change");
    auto gr = [&](RGB rgb)
    {
      for (uint8_t i = 0; i < NUM_STRIPS; i++)
      {
        auto strip = strips[i];

        strip.commit_rgb(rgb, 1);
      }
    };
    gr({255, 170, 0});
    Serial.println("Changed first, changing back");
    delay(1000);
    gr({170, 0, 255});
    Serial.println("Changed back");
  }


  for (uint8_t i = 0; i < NUM_STRIPS; i++) strips[i].show();
#endif
}