#ifndef CONTROLLER_AGENT_H
#define CONTROLLER_AGENT_H

#include <set>
#include <string>

#include "Event.h"
#include "Interfaces/IEventDestination.h"
#include "Interfaces/IEventSubscriber.h"
#include "DeviceAgent.h"

#include <string>
#include <fstream>

//Abstract
class ControllerAgent: public DeviceAgent, public EventDestination
{
protected:
    ControllerAgent(const std::string& _id, EventSubscriber* _subsctiber = 0);
public:
    virtual void Subscribe(const std::string& _type, const std::string& _room);
    virtual void Subscribe(const std::string& _type, const int _floor);

    virtual void Unsubscribe(const std::string& _type, const std::string& _room);
    virtual void Unsubscribe(const std::string& _type, const int _floor);

    void SetSubscriber(EventSubscriber& _sub);
    virtual void SubscriptionList();
public:
// From EventDestination:
    void AcceptEvent(Event*);
    virtual void EventHandle(Event*)=0;
private:
    EventSubscriber*    m_subscriber;
};

#endif