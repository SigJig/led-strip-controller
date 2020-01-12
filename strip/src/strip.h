
#ifndef STRIP_H
#define STRIP_H

#include "colors.h"

class Strip
{
public:
    Strip(ColorPin pins[]);

    void show();
    void clear();

protected:
    ColorPin* m_pins;
    uint8_t m_num_pins;
};

class RGBWStrip : public Strip
{
public:
    using Strip::Strip;

    void set_rgbw(RGBW rgbw);
    void set_hsv(uint16_t hue, double sat, double val);

protected:
    uint8_t m_num_pins = 4;
};

#endif // STRIP_H