#ifndef _HVAC_CONTROLLER_H
#define _HVAC_CONTROLLER_H

#include "ControllerAgent.h"

class HVACController : public ControllerAgent
{
public:
    HVACController(const std::string& _id, EventSubscriber* _subsctiber = 0);
public:
// from eventdestination:
    virtual void EventHandle(Event*);
// from device agent
    virtual void ParseConfigLine(const std::string&) throw (std::invalid_argument);
    virtual void SubscriptionList();
private:
    double      m_temperature;
};

#endif