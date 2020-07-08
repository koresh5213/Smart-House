#ifndef _IEVENT_DESTINATION_H
#define _IEVENT_DESTINATION_H

class Event;

// Interface
class EventDestination
{
public:
    virtual void AcceptEvent(Event*)=0;

    virtual ~EventDestination(){};// TODO remove
};

#endif