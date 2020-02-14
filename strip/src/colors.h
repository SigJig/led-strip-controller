
#ifndef COLORS_H
#define COLORS_H
#include <Arduino.h>

#include "cyclehandler.h"

class ColorPin
{
public:
    ColorPin(uint8_t pin);

    void set_signal(double sig);
    void show(bool dead = false);

    bool move_towards(double sig);

    double get_signal();

protected:
    uint8_t m_pin;
    double m_signal;

    QueueItem* m_queue_item;
};

struct RGB
{
    double r, g, b;

    double* to_list(double* arr);
};

struct RGBW
{
    double r, g, b, w;

    double* to_list(double* arr);
};

struct HSV
{
    double hue, sat, val;

    double* to_list(double* arr);
};

RGB hsv_rgb(HSV hsv);

#endif // COLORS_H