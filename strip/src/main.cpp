
#include <Arduino.h>
// #include <SPI.h>
// #include <WiFiNINA.h>

#include "../config.h"

#define BAUD_RATE 9600
#define ETL_NO_STL

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
    cycle_handler.run();
}