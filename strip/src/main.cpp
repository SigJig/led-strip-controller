
#include <Arduino.h>
#include <SPI.h>
#include <WiFiNINA.h>

#include <config.h>

#define BAUD_RATE 9600

const char* ssid = NETWORK_SSID;
const char* password = NETWORK_PASS;

#include "strip.h"
#include "cyclehandler.h"

ColorPin pins[] = {3, 5, 6};
RGBStrip strip(pins, false);

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

    strip.set_rgb({0, 170, 255});
    strip.init();
}

void loop()
{
    static bool is_red = false;

    if (millis() % (is_red ? 500 : 10000) == 0)
    {
        auto rgb = (is_red ? RGB({255, 255, 255}) : RGB({28, 240, 17}));

        is_red = !is_red;
        
        strip.commit_rgb(rgb);
    }

    led_write(((millis() % 2000) < 500) ? 0xFF : 0x01 );

    cycle_handler.run();
    
    delay(1);
}