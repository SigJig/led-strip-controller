
#ifndef COLORS_H
#define COLORS_H
#include <Arduino.h>

#include "cyclehandler.h"

class ColorPin
{
public:
    ColorPin(uint8_t pin);

    void set_signal(uint8_t sig);
    void show(bool dead = false);

    bool move_towards(uint8_t sig);

    double get_signal();

protected:
    uint8_t m_pin;
    uint8_t m_signal;

    QueueItem* m_queue_item;
};

struct RGB
{
    uint8_t r, g, b;

    uint8_t* to_list(uint8_t arr[3]);
};

struct RGBW
{
    uint8_t r, g, b, w;

    uint8_t* to_list(uint8_t arr[4]);
};

struct HSV
{
    double hue, sat, val;

    uint8_t* to_list(uint8_t arr[3]);
};

struct HSL
{
    double hue, sat, light;

    uint8_t* to_list(uint8_t arr[3]);
};

RGB hsv_rgb(HSV hsv);
RGB hsl_rgb(HSL hsl);

#endif // COLORS_H