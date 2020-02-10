
#include "mqtt.h"
#include "cyclehandler.h"
#include "colors.h"

static void callback(char* topic, byte* payload, unsigned int length)
{
    mqtt_client.publish("output", String("Recieved: [ " + String(topic) + " ] - " + String((char*)payload)).c_str());
}

const char* mqtt_host = MQTT_HOST;
uint16_t mqtt_port = MQTT_PORT;

WiFiClient client;

PubSubClient mqtt_client(mqtt_host, mqtt_port, callback, client);

/*
static String get_until(String str, char delim)
{
    String ret;

    for (uint8_t i = 0; i < str.length(); i++)
    {
        if (str[i] == delim) break;

        ret += ret[i];
    }

    return ret;
}

static void handle_call(uint8_t index, byte* payload, unsigned int length)
{
    if (index >= NUM_STRIPS) return;

    String current;

    String instructions[2] = {""};
    uint8_t instr_idx = 0;

    for (unsigned int i = 0; i < length; i++)
    {
        byte c = payload[i];

        if (isSpace(c))
        {
            instructions[instr_idx] = current;
            instr_idx++;
        }
        else
        {
            current += c;
        }
    }

    PacketCode code = (PacketCode) instructions[0].toInt();
    
    if (!code)
    {
        Serial.println("Invalid code recieved!");
    }

    String type = get_until(instructions[1], '-').toLowerCase();

    instructions[1] = instructions[1].substring(type.length());

    bool is_fade = code & FADE;

    if (type == "rgb")
    {

    }
    else if (type == "rgbw")
    {

    }
    else if (type == "hsv")
    {

    }
}

void process_message(char* topic, byte* payload, unsigned int length)
{
    auto topic_str = String(topic);
    String digit_str;

    for (uint8_t i = 0; i < topic_str.length(); i++)
    {
        char c = topic_str[i];

        if (c == '/') break;

        if (isDigit(c))
        {
            digit_str += c;
        }
    }

    return handle_call(digit_str.toInt(), payload, length);
}
*/