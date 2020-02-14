
#include "colors.h"
#include <math.h>

ColorPin::ColorPin(uint8_t pin) : m_pin(pin), m_signal(0), m_queue_item(nullptr)
{
    pinMode(m_pin, OUTPUT);
}

void ColorPin::set_signal(double sig)
{
    m_signal = sig;
}

void ColorPin::show(bool dead)
{
    analogWrite(m_pin, dead ? 0 : m_signal);
}

bool ColorPin::move_towards(double sig)
{
    if (sig == m_signal) return false;

    set_signal(m_signal + (sig > m_signal) ? 1 : -1);

    return true;
}

double ColorPin::get_signal()
{
    return m_signal;
}

double* RGB::to_list(double* arr)
{
    arr[0] = r;
    arr[1] = g;
    arr[2] = b;

    return arr;
}

double* RGBW::to_list(double* arr)
{
    arr[0] = r;
    arr[1] = g;
    arr[2] = b;
    arr[3] = w;

    return arr;
}

double* HSV::to_list(double* arr)
{
    RGB rgb = hsv_rgb(*this);

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
      return (hsv.val - hsv.val * hsv.sat * max(min(min(k, 4 - k), 1.0), 0.0)) * 255;
    };

    return {f(5), f(3), f(1)};
}