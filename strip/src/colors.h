
#ifndef COLORS_H
#define COLORS_H
#include <Arduino.h>

#include "cyclehandler.h"

class ColorPin
{
public:
    ColorPin(uint8_t pin);

    void set_signal(uint8_t sig);
    void show();

    QueueItem* move_towards(uint8_t sig);

    uint8_t get_signal();

protected:
    uint8_t m_pin;
    uint8_t m_signal;
};

struct RGB { double r, g, b; };
struct RGBW { double r, g, b, w; };

RGB hsv_rgb(uint16_t hue, uint8_t sat, uint8_t val);

#endif // COLORS_H