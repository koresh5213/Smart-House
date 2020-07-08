#ifndef SENSORAGENTH
#define SENSORAGENTH

#include <fstream>

#include "DeviceAgent.h"
#include "Interfaces/IEventSource.h"
#include "Interfaces/IEventReciever.h"
#include "Thread.h"
#include "Event.h"

class SensorAgent;

class Function : public Runnable //TODO -change 'Function' to better name?
{
public:
    Function(SensorAgent*);
    
    virtual void run(void* _in);
private:
    SensorAgent*        m_agent;
};

//Abstract
class SensorAgent : public DeviceAgent, private EventSource
{
friend class Function;
public:
    SensorAgent(const std::string&);
    //~SensorAgent();
public:
    Thread*         RunSensor(void* _data = NULL);
    void            SetReciever(EventReciever*);
protected:
    virtual void*   Activity(void*);
    void            ShootEvent(Event*);
private:
    Function        m_function;
    //ConfigLineParser
    EventReciever*  m_reciever;
};

#endif

/*
Sensor agent shall have those function:
void* Activity(void*);

Sensor agent may have those functions:
ParseConfigLine(const std::string&);

sensor witch is also a controller must inherit virtually

*/