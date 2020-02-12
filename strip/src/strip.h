
#ifndef STRIP_H
#define STRIP_H

#include "colors.h"
#include "cyclehandler.h"

class Strip : public Action
{
public:
    Strip(ColorPin* pins, bool _init = true);

    void init();

    CallbackStatus call();

    void move_towards(double* colors);

    void show();
    void hide();
    void clear();

protected:
    ColorPin* m_pins;

    bool m_shown;

    static const uint8_t num_pins = 3;
};

class RGBStrip : public Strip
{
public:
    using Strip::Strip;

    void commit_rgb(RGB rgb);
    void commit_hsv(HSV hsv);

    void set_rgb(RGB rgb);
    void set_hsv(HSV hsv);

protected:
    static const uint8_t num_pins = 3;
};

class RGBWStrip : public RGBStrip
{
public:
    using RGBStrip::RGBStrip;

    void commit_rgbw(RGBW rgbw);
    void commit_hsv(HSV hsv);

    void set_rgbw(RGBW rgbw);
    void set_hsv(HSV hsv);

protected:
    static const uint8_t num_pins = 4;
};

extern RGBStrip strip;

#endif // STRIP_H