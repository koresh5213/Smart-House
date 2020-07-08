#ifndef _IEVENT_SUBSCRIBER_H
#define _IEVENT_SUBSCRIBER_H

#include <string>

class EventDestination;

// Interface
class EventSubscriber
{
public:
    virtual void Subscribe(EventDestination*, const std::string& _type, const std::string& _room)=0;
    virtual void Subscribe(EventDestination*, const std::string& _type, const int _floor)=0;

    virtual void Unsubscribe(EventDestination*, const std::string& _type, const std::string& _room)=0;
    virtual void Unsubscribe(EventDestination*, const std::string& _type, const int _floor)=0;

    virtual ~EventSubscriber(){};
};

#endif