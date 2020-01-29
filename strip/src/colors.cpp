
#include "colors.h"
#include <cmath>
#include <algorithm>

PinFadeAction::PinFadeAction(ColorPin* pin, uint8_t to)
    : m_pin(pin), m_to(to) {  }

CallbackStatus PinFadeAction::call()
{
    auto signal = m_pin->get_signal();

    if (m_to == signal) return SUCCESS;

    m_pin->set_signal(signal + ((m_to < signal) ? 1 : -1));

    return REPEAT;
}

ColorPin::ColorPin(uint8_t pin) : m_pin(pin), m_signal(0), m_action(nullptr)
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

void ColorPin::move_towards(uint8_t to)
{
    if (m_action != nullptr) cycle_handler.queue_remove(m_action);

    return cycle_handler.add(new PinFadeAction(this, to));
}

uint8_t ColorPin::get_signal()
{
    return m_signal;
}

RGB hsv_rgb(uint16_t hue, uint8_t sat, uint8_t val)
{
    auto f = [&](uint8_t n)
    {
      double k = std::fmod(n + hue / 60.0, 6);
      return (val - val * sat * std::max(std::min(std::min(k, 4 - k), 1.0), 0.0)) * 255;
    };

    return {f(5), f(3), f(1)};
}