
#ifndef STRIP_H
#define STRIP_H

#include "colors.h"
#include "cyclehandler.h"

template<size_t size>
class StripColorHandler : public Action
{
public:
    StripColorHandler(ColorPin pins[size], uint8_t length);
    StripColorHandler(ColorPin pins[size], double colors[size], uint8_t length);

    void set(double colors[size]);
    void on_remove();

    QueueItem* run(bool fade = false);

    CallbackStatus on_call();

protected:
    void remove();

    ColorPin m_pins[size];
    double m_colors[size];

    QueueItem* m_queue_item;

    uint8_t m_size = size;
};

template<size_t size>
class Strip : public Action
{
public:
    Strip(ColorPin* pins, bool _init = true);

    void init();

    CallbackStatus on_call();

    QueueItem* commit(bool fade = false);

    void show(bool show_ = true);
    void clear();

    void set_signals(double* signals);

    bool is_shown();

protected:
    ColorPin m_pins[size];
    StripColorHandler<size> m_handler;

    bool m_shown;
    size_t m_size = size;
};

template<size_t size>
class RGBStrip : public Strip<size>
{
public:
    using Strip::Strip;

    void set_rgb(RGB rgb);
    void set_hsv(HSV hsv);
};

template<size_t size>
class RGBWStrip : public RGBStrip<size>
{
public:
    using RGBStrip::RGBStrip;

    void set_rgbw(RGBW rgbw);
};

extern RGBStrip<3> strip;

#endif // STRIP_H