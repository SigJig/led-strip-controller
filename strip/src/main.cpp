
#include <Arduino.h>
#include <SPI.h>
#include <WiFiNINA.h>

#include "../config.h"

#define BAUD_RATE 9600

const char* ssid = NETWORK_SSID;
const char* password = NETWORK_PASS;

#include "strip.h"
#include "cyclehandler.h"

ColorPin pins[] = {3, 5, 6};
RGBStrip strip(pins);

uint8_t led_pins[] = {9, 10, 11};

void led_write(uint8_t bytes)
{
    for (uint8_t i = 0; i < 3; i++)
    {
        digitalWrite(led_pins[i], (bytes >> i) & 0x01);
    }
}

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

    for (uint8_t i = 0; i < 3; i++) pinMode(led_pins[i], OUTPUT);

    led_write(0xFF);
}

void loop()
{
    static bool is_red = false;
    static uint8_t iteration = 0;

    if (millis() % 4000 == 0)
    {
        Serial.println("Intializing change");
        auto rgb = (is_red ? RGB({0, 170, 255}) : RGB({240, 0, 0}));

        is_red = !is_red;
        
        strip.commit_rgb(rgb);
    }

    iteration = (iteration + 1) % 3;

    led_write(0x01 << iteration);

    cycle_handler.run();
    
    delay(1);
}