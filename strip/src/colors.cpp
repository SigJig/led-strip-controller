
#include "colors.h"
#include <math.h>

ColorPin::ColorPin(uint8_t pin, uint8_t signal) : m_pin(pin), m_signal(signal)
{
    pinMode(m_pin, OUTPUT);
}

void ColorPin::show()
{
    analogWrite(m_pin, m_signal);
}

void ColorPin::set_signal(uint8_t sig)
{
    m_signal = sig;
}

uint8_t ColorPin::get_signal()
{
    return m_signal;
}

RGB hsv_rgb(uint16_t hue, uint8_t sat, uint8_t val)
{
  auto f = [&](uint8_t n)
  {
    double k = fmod(n + hue / 60.0, 6);
    return val - val * sat * max(min(min(k, 4 - k), 1), 0);
  };

  return {f(5) * 255, f(3) * 255, f(1) * 255};
}