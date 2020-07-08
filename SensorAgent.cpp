#include "SensorAgent.h"
#include "Thread.h"

#include <iostream>

using namespace std;

Function::Function(SensorAgent* _agent)
: m_agent(_agent)
{}

void Function::run(void* _in)
{
    m_agent->Activity(_in);
}

SensorAgent::SensorAgent(const string& _id)
: DeviceAgent(_id)
,m_function(this)
,m_reciever(NULL)
{}

Thread* SensorAgent::RunSensor(void* _args)
{
    Thread* thread = new Thread(&m_function, _args);
    return thread;
}

void SensorAgent::SetReciever(EventReciever* _rec)
{
    m_reciever = _rec;
}

void* SensorAgent::Activity(void*) 
{
    return NULL;
}

void SensorAgent::ShootEvent(Event* _event) 
{
    if (m_reciever != NULL)
    {
        m_reciever->RecieveEvent(_event);
    }
}
