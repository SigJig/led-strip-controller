
#include "colors.h"
#include <math.h>

ColorPin::ColorPin(uint8_t pin) : m_pin(pin), m_signal(0), m_queue_item(nullptr)
{
    pinMode(m_pin, OUTPUT);
}

void ColorPin::set_signal(uint8_t sig)
{
    m_signal = sig;
}

void ColorPin::show(bool dead)
{
    analogWrite(m_pin, dead ? 0 : m_signal);
}

bool ColorPin::move_towards(uint8_t sig)
{
    if (sig == m_signal) return false;

    set_signal(m_signal + ((sig > m_signal) ? 1 : -1));

    return true;
}

double ColorPin::get_signal()
{
    return m_signal;
}

uint8_t* RGB::to_list(uint8_t arr[3])
{
    arr[0] = r;
    arr[1] = g;
    arr[2] = b;

    return arr;
}

uint8_t* RGBW::to_list(uint8_t arr[4])
{
    arr[0] = r;
    arr[1] = g;
    arr[2] = b;
    arr[3] = w;

    return arr;
}

uint8_t* HSV::to_list(uint8_t arr[3])
{
    RGB rgb = hsv_rgb(*this);

    arr[0] = rgb.r;
    arr[1] = rgb.g;
    arr[2] = rgb.b;

    return arr;
}

uint8_t* HSL::to_list(uint8_t arr[3])
{
    RGB rgb = hsl_rgb(*this);

    arr[0] = rgb.r;
    arr[1] = rgb.g;
    arr[2] = rgb.b;

    return arr;
}

RGB hsv_rgb(HSV hsv)
{
    auto f = [&](uint8_t n)
    {
      double k = fmod(n + hsv.hue / 60.0, 6);
      return round((hsv.val - hsv.val * hsv.sat * max(min(min(k, 4 - k), 1.0), 0.0)) * 255);
    };

    return {f(5), f(3), f(1)};
}

RGB hsl_rgb(HSL hsl)
{
    auto f = [&](uint8_t n)
    {
        double k = fmod(n + (hsl.hue / 30.0), 12);
        double a = hsl.sat * min(hsl.light, 1.0 - hsl.light);

        return round((hsl.light - a * max(-1, min(min(k - 3, 9 - k), 1))) * 255);
    };

    return {f(0), f(8), f(4)};
}