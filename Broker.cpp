#include "Broker.h"
#include <iostream>
#include <unistd.h>
using namespace std;

BrokerFunction::BrokerFunction(EventBroker* _in)
: m_broker(_in)
{}

void BrokerFunction::run(void*)
{
    m_broker->Broking(NULL);
}

EventBroker::EventBroker(EventGetter& _getter, DeviceFinder& _finder, EventPublisher& _publisher)
: m_function(this)
, m_getter(_getter)
, m_finder(_finder)
, m_publisher(_publisher)
{
}

void EventBroker::PublishMultiple(set<EventDestination*>& _destinationSet, Event* _event)
{
    set<EventDestination*>::iterator itr = _destinationSet.begin();
    set<EventDestination*>::iterator enditr = _destinationSet.end();
    
    for (;itr != enditr; ++itr)
    {
        try
        {
            m_publisher.PublishEvent(*itr, _event);
        }
        catch(...)
        {
            cout << "Error sending event to " << *itr << endl;  // TODO- send to program log
            continue;
        }
    }
}

void* EventBroker::Broking(void*)
{
    Event* e;
    string tempRoom;
    int tempFloor;
    string tempType;
//    for (int i=0;i<20;++i)
    for(;;)
    {
        e = m_getter.WaitForEvent();

        tempRoom = e->Room();
        tempFloor = e->Floor();
        tempType = e->Type();

//        cout << "Broker parsed event " << e->Payload() << " " << e->Room() << " " << e->Type() << " " << e->Floor() << endl;//<<  e->Floor() <<endl;

        set<EventDestination*> subs = m_finder.FindSubscribers(tempType, tempRoom);
        set<EventDestination*> floorsubs = m_finder.FindSubscribers(tempType, tempFloor);

        subs.insert(floorsubs.begin(), floorsubs.end());

        PublishMultiple(subs, e);
        delete e;
    }
    return NULL;
}

Thread* EventBroker::RunBroker()
{
    Thread* thread = new Thread(&m_function, NULL);
    return thread;
}