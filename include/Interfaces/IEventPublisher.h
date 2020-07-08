#ifndef _IEVENT_PUBLISHER_H
#define _IEVENT_PUBLISHER_H

class Event;
class EventDestination;

// Interface
class EventPublisher
{
public:
    virtual void PublishEvent(EventDestination*, Event*)=0;
    virtual ~EventPublisher(){};
};

#endif