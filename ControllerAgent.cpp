#include "ControllerAgent.h"

using namespace std;

ControllerAgent::ControllerAgent(const std::string& _id, EventSubscriber* _subsctiber)
: DeviceAgent(_id)
, m_subscriber(_subsctiber)
{
}

void ControllerAgent::SetSubscriber(EventSubscriber& _sub)
{
    m_subscriber = &_sub;
    SubscriptionList();
}

void ControllerAgent::Subscribe(const std::string& _type, const std::string& _room)
{
    if (m_subscriber == 0)
    {
        return;
    }
    m_subscriber->Subscribe(this, _type, _room);
}

void ControllerAgent::Subscribe(const std::string& _type, const int _floor)
{
    if (m_subscriber == 0)
    {
        return;
    }
    m_subscriber->Subscribe(this, _type, _floor);
}

void ControllerAgent::Unsubscribe(const std::string& _type, const std::string& _room)
{
    if (m_subscriber == 0)
    {
        return;
    }
    m_subscriber->Unsubscribe(this, _type, _room);
}

void ControllerAgent::Unsubscribe(const std::string& _type, const int _floor)
{
    if (m_subscriber == 0)
    {
        return;
    }
    m_subscriber->Unsubscribe(this, _type, _floor);
}

void ControllerAgent::SubscriptionList()
{}

void ControllerAgent::AcceptEvent(Event* _event)
{
    EventHandle(_event);
}