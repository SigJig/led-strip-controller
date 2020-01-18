
#ifndef COLORS_H
#define COLORS_H
#include <Arduino.h>

class ColorPin
{
public:
    ColorPin(uint8_t pin, uint8_t signal = 0);

    void show();
    void set_signal(uint8_t sig);

    bool move_towards(uint8_t sig);

    uint8_t get_signal();

private:
    uint8_t m_pin;
    uint8_t m_signal;
};

struct RGB { double r, g, b; };
struct RGBW { double r, g, b, w; };

RGB hsv_rgb(uint16_t hue, uint8_t sat, uint8_t val);

#endif // COLORS_H