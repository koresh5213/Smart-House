#ifndef BROKERH
#define BROKERH

#include "Interfaces/IEventGetter.h"
#include "Interfaces/IDeviceFinder.h"
#include "Interfaces/IEventPublisher.h"
#include "Thread.h"
#include "Event.h"

#include <set>

class EventBroker;
class EventDestination;

class BrokerFunction : public Runnable
{
public:
                        BrokerFunction(EventBroker*);
    virtual void run(void* _in);
private:
    EventBroker*        m_broker;
};
 
class EventBroker
{
friend class BrokerFunction;
public:
            EventBroker(EventGetter&, DeviceFinder&, EventPublisher&);
public:
    Thread*             RunBroker();
private:
    void*               Broking(void*);
    void                PublishMultiple(std::set<EventDestination*>&, Event*);
    
private:
    BrokerFunction      m_function;
    EventGetter&        m_getter;
    DeviceFinder&       m_finder;
    EventPublisher&     m_publisher;
};

#endif