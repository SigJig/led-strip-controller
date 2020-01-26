
#ifndef CYCLEHANDLER_H
#define CYCLEHANDLER_H

#include <Arduino.h>

enum CallbackStatus : uint8_t
{
    SUCCESS = 0x00,
    ERROR = 0x01,
    REPEAT = 0x02,
};

struct QueueItem
{
    QueueItem* next = nullptr;
    T& cb;
};

class _CycleHandler
{
public:
    _CycleHandler();

    QueueItem* add(Functor& cb);

    void run();
    void clear();

protected:
    void process_callback(QueueItem* qi);

    QueueItem* m_queue;
};

extern _CycleHandler cycle_handler;

#endif // CYCLEHANDLER_H