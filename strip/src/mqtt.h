
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

template<typename Functor>
String scan_func(String& str, Functor f);

String scan_delim(String& str, char delim);

template<typename T>
T* extract_values(String& str, T* arr, uint8_t length);

void mqtt_callback(char* topic, byte* message, unsigned int length);
void process_instruction(PacketCode code, String args);
void parse_message(byte* message, unsigned int length);

extern PubSubClient mqtt_client;

#endif // MQTT_H