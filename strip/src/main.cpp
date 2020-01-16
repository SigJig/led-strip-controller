
#include <Arduino.h>
#include <SPI.h>
#include <WiFiNINA.h>

#include "../config.h"

#define BAUD_RATE 9600

const char* ssid = SSID;
const char* password = PASSWORD;

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
}

void loop()
{

}