
#ifndef CYCLEHANDLER_H
#define CYCLEHANDLER_H

#include <Arduino.h>
#include <vector>
#include <memory>

#include "cyclehandler.h"

enum CallbackStatus : uint8_t
{
    SUCCESS = 0x00,
    ERROR = 0x01,
    REPEAT = 0x02,
};

class Action
{
    virtual CallbackStatus call() = 0;
};

class _CycleHandler
{
public:
    _CycleHandler();

    void add(Action* action); // TODO: Return iterator pointer

    bool queue_remove(Action* qi); // TODO: Take iterator pointer instead

    void run();
    void clear();

protected:
    void process_callback(Action* qi); // TODO: Might just directly call the action method instead

    std::vector<std::unique_ptr<Action>> m_queue;
};

extern _CycleHandler cycle_handler;

#endif // CYCLEHANDLER_H