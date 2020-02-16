
#ifndef STRIP_H
#define STRIP_H

#include "colors.h"
#include "cyclehandler.h"

template<size_t size>
class StripColorHandler : public Action
{
public:
    StripColorHandler(ColorPin pins[size]);
    StripColorHandler(ColorPin pins[size], uint8_t colors[size]);

    void set(uint8_t colors[size]);
    void on_remove();

    QueueItem* run(bool fade = false);

    CallbackStatus on_call();

protected:
    void remove();

    ColorPin* m_pins;
    uint8_t m_colors[size];

    QueueItem* m_queue_item;

    uint8_t m_size = size;
};

template<size_t size>
class Strip : public Action
{
public:
    Strip(ColorPin pins[size], bool _init = true);

    void init();

    CallbackStatus on_call();

    QueueItem* commit(bool fade = false);

    void show(bool show_ = true);
    void clear();

    void set_signals(uint8_t* signals);

    bool is_shown();

protected:
    ColorPin* m_pins;
    StripColorHandler<size> m_handler;

    bool m_shown;
    size_t m_size = size;
};

template<size_t size = 3>
class _RGBStrip : public Strip<size>
{
public:
    using Strip<size>::Strip;

    void set_rgb(RGB rgb);
    void set_hsv(HSV hsv);
};

template<size_t size = 4>
class _RGBWStrip : public _RGBStrip<size>
{
public:
    using _RGBStrip<size>::_RGBStrip;

    void set_rgbw(RGBW rgbw);
};

typedef _RGBWStrip<> RGBWStrip;
typedef _RGBStrip<> RGBStrip;

extern RGBStrip strip;

#include "strip.tpp"

#endif // STRIP_H