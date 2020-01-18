
#include "strip.h"

Strip::Strip(ColorPin pins[])
    : m_pins(pins)
{  }

void Strip::show()
{
    for (uint8_t i = 0; i < m_num_pins; i++)
    {
        m_pins[i].show();
    }
}

void Strip::clear()
{
    for (uint8_t i = 0; i < m_num_pins; i++)
    {
        m_pins[i].set_signal(0);
    }
}

void RGBStrip::set_rgb(RGB rgb)
{
    m_pins[0].set_signal(rgb.r);
    m_pins[1].set_signal(rgb.g);
    m_pins[2].set_signal(rgb.b);
}

void RGBStrip::set_hsv(uint16_t hue, double sat, double value)
{
    set_rgb(hsv_rgb(hue, sat, value));
}

void RGBWStrip::set_hsv(uint16_t hue, double sat, double value)
{
    RGB rgb = hsv_rgb(hue, sat, value);

    set_rgbw({rgb.r, rgb.g, rgb.b, (1.0 - value) * 255.0});
}

void RGBWStrip::set_rgbw(RGBW rgbw)
{
    RGBStrip::set_rgb({rgbw.r, rgbw.g, rgbw.b});

    m_pins[3].set_signal(rgbw.w);
}

void RGBWStrip::commit_rgbw(RGBW rgbw, unsigned long ms)
{
    double color_list[] = {rgbw.r, rgbw.g, rgbw.b, rgbw.w};

    auto still_valid = [&]()
    {
        bool valid = false;

        for (uint8_t i = 0; i < m_num_pins; i++)
        {
            if (m_pins[i].move_towards(color_list[i])) valid = true;
        }

        return valid;
    };

    while (still_valid())
    {
        show();

        delay(ms);
    }
}