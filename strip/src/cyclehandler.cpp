
#include <string.h>

#include "cyclehandler.h"

_CycleHandler cycle_handler;

CallbackStatus Action::call()
{
    // TODO: Throw error
    Serial.println("Base function called");

    return ERROR;
}

QueueItem::QueueItem() {  }

QueueItem::~QueueItem()
{
    destroy();
}

bool QueueItem::add(Action* action)
{
    if (!(is_free() && cycle_handler.occupy(this)))
    {
        return false;
    }

    m_ptr = action;

    return true;
}


bool QueueItem::is_free()
{
    return m_ptr == nullptr;
}

void QueueItem::destroy()
{
    cycle_handler.free(this);
    delete m_ptr;
}

Action& QueueItem::operator*() const
{
    return *m_ptr;
}

Action* QueueItem::operator->() const
{
    return m_ptr;
}

_CycleHandler::_CycleHandler()
    : size(QUEUE_MAX_SIZE), m_free_map(0)
{  }

QueueItem* _CycleHandler::add(Action* action)
{
    auto i = next_free();
    if (i == nullptr)
    {
        return nullptr;
    }

    i->add(action);

    return i;
}

void _CycleHandler::queue_remove(QueueItem* item)
{
    item->destroy();
}

void _CycleHandler::process_callback(QueueItem* item)
{
    CallbackStatus ret = (*item)->call();

    if (ret & ERROR)
    {
        // GOOGOGO GAGAGA HANDLE ERROR
    }
    else if (!(ret & REPEAT)) // Remove the queue item if its not supposed to repeat
    {
        queue_remove(item);
    }
}

uint8_t _CycleHandler::get_index(QueueItem* item)
{
    if (!(item >= m_queue && item < (m_queue + size)))
    {
        // TODO: Error
        return size;
    }

    uint8_t index = item - m_queue;

    if (index)
    {
        size_t queue_size = sizeof(QueueItem);

        if (index % queue_size != 0)
        {
            // TODO: Error

            return size;
        }

        index /= queue_size;
    }

    return index;
}

void _CycleHandler::free(QueueItem* item)
{
    auto index = get_index(item);

    if (index < size)
    {
        m_free_map &= ~(0x01 << index);
    }
    else
    {
        // TODO: Throw error (?)
    }
}

bool _CycleHandler::occupy(QueueItem* item)
{
    auto index = get_index(item);

    if (index == size)
    {
        return false;
    }

    m_free_map |= 0x01 << index;

    return true;
}

void _CycleHandler::run()
{
    for (uint8_t i = 0; i < size; i++)
    {
        process_callback(&m_queue[i]);
    }
}

void _CycleHandler::clear()
{
    for (uint8_t i = 0; i < size; i++)
    {
        m_queue[i].destroy();
    }
}

QueueItem* _CycleHandler::next_free()
{
    if (m_free_map)
    {
        for (uint8_t i = 0; i < size; i++)
        {
            if ((m_free_map >> i) & 0x01) return &m_queue[i];
        }
    }

    return nullptr;
}