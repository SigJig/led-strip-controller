
#include <Arduino.h>
// #include <SPI.h>
// #include <WiFiNINA.h>

#include "../config.h"

#define BAUD_RATE 9600

const char* ssid = NETWORK_SSID;
const char* password = NETWORK_PASS;

#include "strip.h"
#include "cyclehandler.h"

#define NUM_STRIPS 2

ColorPin s1[] = {3, 5, 6};
ColorPin s2[] = {9, 10, 11};

RGBStrip strips[NUM_STRIPS] = {s1, s2};

void setup()
{
    Serial.begin(BAUD_RATE);

    Serial.println("Connecting to Wifi");
    /* WiFi.begin(ssid, password);

    for (int time = millis(); WiFi.status() != WL_CONNECTED; time = millis())
    {
      if ((time % 2000) == 0) Serial.println("Connecting...");
    }
 */
    Serial.println("Wifi connection established");
}

void loop()
{
    static bool is_red = false;

    if (millis() % 4000)
    {
      Serial.println("Intializing change");
      auto rgb = (is_red ? RGB({0, 170, 255}) : RGB({240, 0, 0}));

      is_red = !is_red;

      for (uint8_t i = 0; i < 2; i++) strips[i].commit_rgb(rgb);
    }

    cycle_handler.run();
    delay(1);
}