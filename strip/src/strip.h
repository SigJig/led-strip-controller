
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

class RGBStrip : public Strip
{
public:
    using Strip::Strip;

    void set_rgb(RGB rgb);
    void set_hsv(uint16_t hue, double sat, double val);
private:
    uint8_t m_num_pins = 3;
};

class RGBWStrip : public RGBStrip
{
public:
    using RGBStrip::RGBStrip;

    void set_rgbw(RGBW rgbw);
    void set_hsv(uint16_t hue, double sat, double val);
private:
    uint8_t m_num_pins = 4;
};

#endif // STRIP_H