#ifndef EVENTSENDER_H
#define EVENTSENDER_H

#include "Interfaces/IEventPublisher.h"

class EventSender : public EventPublisher
{
public:
    virtual void PublishEvent(EventDestination*, Event*);
};

#endif