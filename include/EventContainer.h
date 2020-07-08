#ifndef _EVENT_CONTAINER_H
#define _EVENT_CONTAINER_H

#include "Interfaces/IEventReciever.h"
#include "Interfaces/IEventGetter.h"
#include "WaitableQueue/WQueue.h"
#include "Event.h"
#include <set>


class EventContainer : public EventReciever, public EventGetter
{
public:
            EventContainer(unsigned int _size);
        //  ~EventContainer();
public:
    virtual void        RecieveEvent(Event*);
    virtual Event*      WaitForEvent();
public:
    void PrintSize();
private:
//Non copyable
            EventContainer(const EventContainer&);
    EventContainer& operator=(const EventContainer&);
private:
    WQueue<Event*>          m_wq;
};

#endif 