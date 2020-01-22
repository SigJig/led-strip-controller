
#ifndef CYCLEHANDLER_H
#define CYCLEHANDLER_H

#include <Arduino.h>

enum CallbackStatus : uint8_t
{
    ERROR = 0x01,
    REPEAT = 0x02,
};

typedef CallbackStatus (*callback_fnc)();

struct QueueItem
{
    QueueItem* next = nullptr;
    callback_fnc cb;
};

class _CycleHandler
{
public:
    _CycleHandler();

    void add(callback_fnc cb);

    void run();
    void clear();

protected:
    void process_callback(QueueItem* qi);

    QueueItem* m_queue;
};

extern _CycleHandler cycle_handler;

#endif // CYCLEHANDLER_H