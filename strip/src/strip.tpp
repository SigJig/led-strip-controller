
#include "strip.h"

template<size_t size>
StripColorHandler<size>::StripColorHandler(ColorPin pins[size])
    : m_pins(pins), m_queue_item(nullptr), m_turn_off(false)
{  }

template<size_t size>
StripColorHandler<size>::StripColorHandler(ColorPin pins[size], uint8_t colors[size])
    : m_pins(pins), m_queue_item(nullptr), m_turn_off(false)
{
    set(colors);
}

template<size_t size>
CallbackStatus StripColorHandler<size>::on_call()
{
    CallbackStatus status = SUCCESS;

    for (uint8_t i = 0; i < m_size; i++)
    {
        if (m_pins[i].move_towards(m_turn_off ? 0 : m_colors[i]))
        {
            status = REPEAT;
        }
    }

    return status;
}

template<size_t size>
void StripColorHandler<size>::set(uint8_t colors[size])
{
    for (size_t i = 0; i < size; i++) m_colors[i] = colors[i];
}

template<size_t size>
void StripColorHandler<size>::on_remove()
{
    m_queue_item = nullptr;
}

template<size_t size>
QueueItem* StripColorHandler<size>::add_to_queue()
{
    if (m_queue_item != nullptr)
    {
        cycle_handler.queue_remove(m_queue_item);
    }
    
    m_queue_item = cycle_handler.add(this);

    return m_queue_item;
}

template<size_t size>
QueueItem* StripColorHandler<size>::run(bool fade)
{
    if (!fade)
    {
        for (uint8_t i = 0; i < m_size; i++)
        {
            m_pins[i].set_signal(m_colors[i]);
        }

        return nullptr;
    }

    return this->add_to_queue();
}

template<size_t size>
QueueItem* StripColorHandler<size>::toggle(bool on, bool fade)
{
    m_turn_off = !on;

    if (m_turn_off && !fade)
    {
        for (uint8_t i = 0; i < m_size; i++)
        {
            m_pins[i].set_signal(0);
        }

        return nullptr;
    }

    return this->run(fade);
}

template<size_t size>
Strip<size>::Strip(ColorPin pins[size], bool _init)
    : m_pins(pins), m_handler(m_pins), m_shown(true)
{
    if (_init)
    {
        init();
    }
}

template<size_t size>
void Strip<size>::init()
{
    cycle_handler.add(this);
}

template<size_t size>
CallbackStatus Strip<size>::on_call()
{
    for (uint8_t i = 0; i < m_size; i++)
    {
        m_pins[i].show(!m_shown);
    }

    return REPEAT;
}

template<size_t size>
void Strip<size>::show(bool show_)
{
    m_shown = show_;
}

template<size_t size>
void Strip<size>::clear()
{
    for (uint8_t i = 0; i < m_size; i++) m_pins[i].set_signal(0);
}

template<size_t size>
void Strip<size>::set_signals(uint8_t* signals)
{
    m_handler.set(signals);
}

template<size_t size>
bool Strip<size>::is_shown()
{
    return m_shown;
}

template<size_t size>
QueueItem* Strip<size>::commit(bool fade)
{
    return m_handler.run(fade);
}

template<size_t size>
QueueItem* Strip<size>::toggle(bool on, bool fade)
{
    return m_handler.toggle(on, fade);
}

template<size_t size>
void _RGBStrip<size>::set_rgb(RGB rgb)
{   
    uint8_t list[3];
    
    this->set_signals(rgb.to_list(list));
}

template<size_t size>
void _RGBStrip<size>::set_hsv(HSV hsv)
{
    set_rgb(hsv_rgb(hsv));
}

template<size_t size>
void _RGBStrip<size>::set_hsl(HSL hsl)
{
    set_rgb(hsl_rgb(hsl));
}

template<size_t size>
void _RGBWStrip<size>::set_rgbw(RGBW rgbw)
{
    uint8_t list[4];
    
    this->set_signals(rgbw.to_list(list));
}
