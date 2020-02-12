
#include "mqtt.h"
#include "cyclehandler.h"
#include "colors.h"
#include "strip.h"

const char* mqtt_host = MQTT_HOST;
uint16_t mqtt_port = MQTT_PORT;

WiFiClient client;
PubSubClient mqtt_client(mqtt_host, mqtt_port, mqtt_callback, client);

template<typename Functor>
String scan_func(String& str, Functor f)
{
    String ret;
    uint8_t i = 0;

    for (; i < str.length(); i++)
    {
        char c = str[i];

        if (f(c))
        {
            break;
        }

        ret += c;
    }

    str.remove(0, i + 1);

    return ret;
}

String scan_delim(String& str, char delim)
{
    return scan_func(str, [&delim](char c){ return c == delim; });
}

template<typename T>
T* extract_values(String& str, T* arr, uint8_t length)
{
    for (uint8_t i = 0; i < length; i++)
    {
        String val = scan_delim(str, '-');

        if (!val)
        {
            // TODO: Error
        }

        arr[i] = val.toInt();
    }

    return arr;
}

void process_instruction(PacketCode code, String args)
{
    String mode = scan_delim(args, '-');
    mode.toLowerCase();

    if (mode == "rgb")
    {
        double values[3];
        extract_values(args, values, 3);

        RGB rgb = {values[0], values[1], values[2]};
        strip.commit_rgb(rgb);
    }
    else if (mode == "hsv")
    {
        double values[3];
        extract_values(args, values, 3);

        HSV hsv = {values[0], values[1], values[2]};
        strip.commit_hsv(hsv);
    }
    else
    {
        // TODO: Error
    }
}

void parse_message(byte* message, unsigned int length)
{
    String instruction, message_str;

    for (unsigned int i = 0; i < length; i++)
    {
        char m = message[i];
        message_str += m;
    }

    instruction = scan_func(message_str, [](char c){ return isspace(c); });

    return process_instruction((PacketCode)instruction.toInt(), message_str);
}

void mqtt_callback(char* topic, byte* payload, unsigned int length)
{
    parse_message(payload, length);
}