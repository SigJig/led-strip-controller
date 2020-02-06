
#ifndef CYCLEHANDLER_H
#define CYCLEHANDLER_H

#include <Arduino.h>

#ifndef QUEUE_MAX_SIZE
    #define QUEUE_MAX_SIZE 10
#endif

#include "cyclehandler.h"

enum CallbackStatus : uint8_t
{
    SUCCESS = 0x00,
    ERROR = 0x01,
    REPEAT = 0x02
};

class Action
{
public:
    virtual ~Action();
    virtual CallbackStatus call();
};

/**
 * This class acts as a smart pointer to Action*
 * 
 */
class QueueItem
{
public:
    QueueItem();
    ~QueueItem();

    bool is_free();
    bool add(Action* action);
    
    void destroy();

    Action& operator*() const;
    Action* operator->() const;

protected:
    Action* m_ptr;
};

class _CycleHandler
{
public:
    typedef
#if QUEUE_MAX_SIZE > 64
    uint128_t
#elif QUEUE_MAX_SIZE > 32
    uint64_t
#elif QUEUE_MAX_SIZE > 16
    uint32_t
#elif QUEUE_MAX_SIZE > 8
    uint16_t
#else
    uint8_t
#endif
    map_size_t;

    _CycleHandler();

    QueueItem* add(Action* action); // TODO: Return iterator pointer
    void queue_remove(QueueItem* item); // TODO: Take iterator pointer instead

    void free(QueueItem* item);
    bool occupy(QueueItem* item);

    void run();
    void clear();

    const uint8_t size;

protected:
    void process_callback(QueueItem* item); // TODO: Might just directly call the action method instead
    uint8_t get_index(QueueItem* item);

    QueueItem* next_free();
    map_size_t m_free_map;

    QueueItem m_queue[QUEUE_MAX_SIZE];
};

extern _CycleHandler cycle_handler;

#endif // CYCLEHANDLER_H