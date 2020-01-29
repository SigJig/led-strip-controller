
#ifndef COLORS_H
#define COLORS_H
#include <Arduino.h>

#include "cyclehandler.h"

class PinFadeAction : public Action
{
public:
    PinFadeAction(ColorPin* pin, uint8_t to);

    CallbackStatus call();

protected:
    uint8_t m_to;

    ColorPin* m_pin;
};

class ColorPin
{
public:
    ColorPin(uint8_t pin);

    void set_signal(uint8_t sig);
    void show(bool dead = false);

    void move_towards(uint8_t sig);

    uint8_t get_signal();

protected:
    uint8_t m_pin;
    uint8_t m_signal;

    Action* m_action;

    friend class PinFadeAction;
};

struct RGB { double r, g, b; };
struct RGBW { double r, g, b, w; };

RGB hsv_rgb(uint16_t hue, uint8_t sat, uint8_t val);

#endif // COLORS_H