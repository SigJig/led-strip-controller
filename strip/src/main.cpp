
#include <Arduino.h>
#include <config.h>

#define BAUD_RATE 9600

#include "mqtt.h"
#include "strip.h"
#include "cyclehandler.h"
#include "wifi.h"

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
    connect();

    for (uint8_t i = 0; i < 3; i++) pinMode(led_pins[i], OUTPUT);

    strip.init();
}

void loop()
{
    if (!mqtt_client.connected())
    {
        if (mqtt_client.connect("arduino-strips"))
        {
            mqtt_client.publish("output", "Connected");
            mqtt_client.subscribe("strips/+");
        }
        delay(5000);
    }
    else
    {
        mqtt_client.loop();
        cycle_handler.run();

        delay(1);
    }
    
    
}