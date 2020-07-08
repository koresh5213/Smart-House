#ifndef _IEVENT_SOURCE_H
#define _IEVENT_SOURCE_H

class Event;

class EventSource
{
public:
    virtual ~EventSource(){};
protected:
    virtual void ShootEvent(Event*)=0;
//TODO- make all interfaces non-copyable
};

#endif