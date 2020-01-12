
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

void RGBWStrip::set_hsv(uint16_t hue, double sat, double value)
{
    RGB rgb = hsv_rgb(hue, sat, value);

    set_rgbw({rgb.r, rgb.g, rgb.b, (1.0 - value) * 255.0});
}

void RGBWStrip::set_rgbw(RGBW rgbw)
{
    m_pins[0].set_signal(rgbw.r);
    m_pins[1].set_signal(rgbw.g);
    m_pins[2].set_signal(rgbw.b);
    m_pins[3].set_signal(rgbw.w);
}