
#include "strip.h"


ColorPin pins[] = {3, 5, 6};
RGBStrip strip(pins, false);

Strip::Strip(ColorPin* pins, bool _init)
    : m_pins(pins), m_shown(true)
{
    if (_init)
    {
        init();
    }
}

void Strip::init()
{
    cycle_handler.add(this);
}

CallbackStatus Strip::call()
{
    for (uint8_t i = 0; i < num_pins; i++)
    {
        m_pins[i].show(!m_shown);
    }

    return REPEAT;
}

void Strip::show()
{
    m_shown = true;
}

void Strip::hide()
{
    m_shown = false;
}

void Strip::clear()
{
    for (uint8_t i = 0; i < num_pins; i++) m_pins[i].set_signal(0);
}

void Strip::move_towards(double* colors)
{
    for (uint8_t i = 0; i < num_pins; i++)
    {
        m_pins[i].move_towards(colors[i]);
    }
}

void RGBStrip::set_rgb(RGB rgb)
{   
    clear();
    m_pins[0].set_signal(rgb.r);
    m_pins[1].set_signal(rgb.g);
    m_pins[2].set_signal(rgb.b);
}

void RGBStrip::set_hsv(HSV hsv)
{   
    clear();
    set_rgb(hsv_rgb(hsv));
}

void RGBStrip::commit_rgb(RGB rgb)
{
    double colors[] = {rgb.r, rgb.g, rgb.b};

    return move_towards(colors);
}

void RGBStrip::commit_hsv(HSV hsv)
{
    RGB rgb = hsv_rgb(hsv);

    return commit_rgb(rgb);
}

void RGBWStrip::set_hsv(HSV hsv)
{
    RGB rgb = hsv_rgb(hsv);

    set_rgbw({rgb.r, rgb.g, rgb.b, (1.0 - hsv.val) * 255.0});
}

void RGBWStrip::set_rgbw(RGBW rgbw)
{
    set_rgb({rgbw.r, rgbw.g, rgbw.b});

    m_pins[3].set_signal(rgbw.w);
}

void RGBWStrip::commit_rgbw(RGBW rgbw)
{
    double color_list[] = {rgbw.r, rgbw.g, rgbw.b, rgbw.w};

    return move_towards(color_list);
}