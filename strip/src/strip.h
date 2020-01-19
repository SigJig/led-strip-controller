
#ifndef STRIP_H
#define STRIP_H

#include "colors.h"
#include <vector>

class Strip
{
public:
    Strip(const std::vector<ColorPin> pins);

    bool move_towards(double* colors);

    void commit(double* colors, unsigned long ms);

    void show();
    void clear();

protected:
    const std::vector<ColorPin> m_pins;
};

class RGBStrip : public Strip
{
public:
    using Strip::Strip;
    void commit_rgb(RGB rgb, unsigned long ms);

    void set_rgb(RGB rgb);
    void set_hsv(uint16_t hue, double sat, double val);
};

class RGBWStrip : public RGBStrip
{
public:
    using RGBStrip::RGBStrip;

    void commit_rgbw(RGBW rgbw, unsigned long ms);

    void set_rgbw(RGBW rgbw);
    void set_hsv(uint16_t hue, double sat, double val);
};

#endif // STRIP_H