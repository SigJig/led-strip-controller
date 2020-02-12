
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

    QueueItem* move_towards(uint8_t sig);

    uint8_t get_signal();

protected:
    uint8_t m_pin;
    uint8_t m_signal;

    QueueItem* m_queue_item;

    friend class PinFadeAction;
};

class PinFadeAction : public Action
{
public:
    PinFadeAction(ColorPin* pin, uint8_t to);

    CallbackStatus call();

protected:
    ColorPin* m_pin;

    uint8_t m_to;
};

struct RGB { double r, g, b; };
struct RGBW { double r, g, b, w; };

struct HSV { double hue, sat, val; };

RGB hsv_rgb(HSV hsv);

#endif // COLORS_H