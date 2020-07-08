#include "Agents/FireSafetySensor.h"

#include <string>
#include <iostream>

using namespace std;

FireSafetySensor::FireSafetySensor(const std::string& _id)
: SensorAgent(_id)
{
}
 
FireSafetySensor::~FireSafetySensor(){}

void* FireSafetySensor::Activity(void* _input)
{
//    cout << "Fire sensor is active, listening on signal " << strsignal(m_signum) << endl;
    return 0;
}

void FireSafetySensor::HandleSignal()
{
    cout << "Got it" << endl;
}

 void FireSafetySensor::ParseConfigLine(const std::string& _line) throw (std::invalid_argument)
 {
    
    if (_line.find("SIGUSR1") != string::npos )
    {
        m_signum = SIGUSR1;
    }
    m_signum = SIGUSR2;
 }

 void FireSafetySensor::SignalSubscribeList()
 {
     cout << "subscribe list" << endl;
    SubscribeToSignal(m_signum);
 }


 extern "C" string TypeName()
{
    return "fire_safety";
}

extern "C" DeviceAgent* Creator(const string& _id)
{
    return new FireSafetySensor(_id);
}