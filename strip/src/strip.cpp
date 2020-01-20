
#include "strip.h"

Strip::Strip(std::vector<ColorPin> pins)
    : m_pins(pins)
{  }

void Strip::show()
{
    for (auto i : m_pins) i.show();
}

void Strip::clear()
{
    for (auto i : m_pins) i.set_signal(0);
}

bool Strip::move_towards(double* colors)
{
    bool valid = false;

    for (uint8_t i = 0; i < m_pins.size(); i++)
    {
        auto pin = m_pins[i];

        if (pin.move_towards(colors[i])) valid = true;
    }

    return valid;
}

void Strip::commit(double* colors, unsigned long ms)
{
    while (move_towards(colors))
    {
        show();

        delay(ms);
    }
}

void RGBStrip::set_rgb(RGB rgb)
{   
    clear();
    m_pins[0].set_signal(rgb.r);
    m_pins[1].set_signal(rgb.g);
    m_pins[2].set_signal(rgb.b);
}

void RGBStrip::set_hsv(uint16_t hue, double sat, double value)
{   
    clear();
    set_rgb(hsv_rgb(hue, sat, value));
}

void RGBStrip::commit_rgb(RGB rgb, unsigned long ms)
{
    double colors[] = {rgb.r, rgb.g, rgb.b};

    return commit(colors, ms);
}

void RGBWStrip::set_hsv(uint16_t hue, double sat, double value)
{
    RGB rgb = hsv_rgb(hue, sat, value);

    set_rgbw({rgb.r, rgb.g, rgb.b, (1.0 - value) * 255.0});
}

void RGBWStrip::set_rgbw(RGBW rgbw)
{
    set_rgb({rgbw.r, rgbw.g, rgbw.b});

    m_pins[3].set_signal(rgbw.w);
}

void RGBWStrip::commit_rgbw(RGBW rgbw, unsigned long ms)
{
    double color_list[] = {rgbw.r, rgbw.g, rgbw.b, rgbw.w};

    return commit(color_list, ms);
}