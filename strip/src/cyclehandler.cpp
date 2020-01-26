
#include "cyclehandler.h"

_CycleHandler cycle_handler;

_CycleHandler::_CycleHandler()
    : m_queue(nullptr)
{  }

QueueItem* _CycleHandler::add(std::function<CallbackStatus()> cb)
{
    QueueItem* qi = new QueueItem();

    qi->cb = cb;

    QueueItem* _i = m_queue;
    if (_i == nullptr)
    {
        _i = qi;
    }
    else
    {
        while (_i->next != nullptr)
        {
            _i = _i->next;
        }

        _i->next = qi;
    }

    return qi;
}

void _CycleHandler::queue_remove(QueueItem* qi)
{
    qi->last->next = qi->next;
    qi->next->last = qi->last;

    delete qi;
}

void _CycleHandler::process_callback(QueueItem* qi)
{
    CallbackStatus ret = qi->cb();

    if (ret & ERROR)
    {
        // GOOGOGO GAGAGA HANDLE ERROR
    }
    else if (!(ret & REPEAT)) // Remove the queue item if its not supposed to repeat
    {
        queue_remove(qi);
    }
}

void _CycleHandler::run()
{
    QueueItem* qi = m_queue;

    if (qi == nullptr) return;

    do
    {
        process_callback(qi);

        qi = qi->next;
    } while (qi != nullptr);
}

void _CycleHandler::clear()
{
    for (QueueItem* qi = m_queue; qi->next != nullptr;)
    {
        auto next = qi->next;
        delete qi;

        qi = next;
    }
}