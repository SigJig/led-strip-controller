
#include "colors.h"
#include <math.h>

ColorPin::ColorPin(uint8_t pin) : m_pin(pin), m_signal(0)
{
    pinMode(m_pin, OUTPUT);
}

void ColorPin::set_signal(uint8_t sig)
{
    m_signal = sig;
}

void ColorPin::show()
{
    analogWrite(m_pin, m_signal);
}

QueueItem* ColorPin::move_towards(uint8_t to)
{
    return cycle_handler.add([&, this]()
    {
        if (to == this->m_signal) return SUCCESS;

        this->set_signal(this->m_signal + (to < this->m_signal ? 1 : -1));

        return REPEAT;
    });
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