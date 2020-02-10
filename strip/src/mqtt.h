
#ifndef MQTT_H
#define MQTT_H

#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFiNINA.h>

#include <config.h>

enum PacketCode : uint8_t {
    NA = 0b00,
    OFF = 0b01,
    ON = 0b10,
    FADE = 0b100
};

//void process_message(char* topic, byte* payload, unsigned int length);

extern PubSubClient mqtt_client;

#endif // MQTT_H