
#ifndef STRIP_H
#define STRIP_H

#include "colors.h"
#include "cyclehandler.h"

class Strip
{
public:
    Strip(ColorPin* pins);

    bool move_towards(double* colors);

    void show();
    void clear();

protected:
    ColorPin* m_pins;

    bool m_shown;
    QueueItem* m_queue_item;

    static const uint8_t num_pins = 3;
};

class RGBStrip : public Strip
{
public:
    using Strip::Strip;

    void commit_rgb(RGB rgb);

    void set_rgb(RGB rgb);
    void set_hsv(uint16_t hue, double sat, double val);

protected:
    static const uint8_t num_pins = 3;
};

class RGBWStrip : public RGBStrip
{
public:
    using RGBStrip::RGBStrip;

    void commit_rgbw(RGBW rgbw);

    void set_rgbw(RGBW rgbw);
    void set_hsv(uint16_t hue, double sat, double val);

protected:
    static const uint8_t num_pins = 4;
};

#endif // STRIP_H