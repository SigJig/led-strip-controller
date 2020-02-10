

#ifndef WIFI_H
#define WIFI_H

#include <SPI.h>
#include <WiFiNINA.h>

#include <config.h>

const char* ssid = NETWORK_SSID;
const char* password = NETWORK_PASS;

inline void connect()
{
    Serial.println("Connecting to Wifi");
    WiFi.begin(ssid, password);

    for (int time = millis(); WiFi.status() != WL_CONNECTED; time = millis())
    {
        if ((time % 2000) == 0) Serial.println("Connecting...");
    }

    Serial.println("Wifi connection established");
}

#endif // WIFI_H