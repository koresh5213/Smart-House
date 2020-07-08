#ifndef FIRE_SAFETY_SENSOR_H
#define FIRE_SAFETY_SENSOR_H

#include "SensorAgent.h"
#include "SignalRegistry.h"

#include <signal.h>

class FireSafetySensor: public SensorAgent, public SigHandler
{
public:
    FireSafetySensor(const std::string& _id);
    virtual ~FireSafetySensor();
private:
// from sensor agent:
    virtual void*   Activity(void*);
    virtual void    ParseConfigLine(const std::string&) throw (std::invalid_argument);
private:
// from signal handler:
    virtual void HandleSignal();
    virtual void SignalSubscribeList();
private:
    int             m_signum;
};

#endif