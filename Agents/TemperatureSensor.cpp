#include "Agents/TemperatureSensor.h"
#include <iostream> // for debug
#include <algorithm> // for remove_if
#include <stdlib.h> // for strtod
#include <time.h>   // for time
#include <unistd.h>  // for sleep
#include <sstream>  // for double to string conversion
using namespace std;


TemperatureSensor::TemperatureSensor(const string& _id)
: SensorAgent(_id)
{
    SetType("ambient_temp");
}

void TemperatureSensor::ParseConfigLine(const std::string& _line)throw (std::invalid_argument)
{
    string unit, lower, upper, period;
    unit = GetParameter(_line, "units:");
    lower = GetParameter(_line, "lower:");
    upper = GetParameter(_line, "upper:");
    period = GetParameter(_line, "period:");

    //cout << "'" << unitIndex << "' '" << lowerIndex << "' '" << upperIndex << "' '" << periodIndex << "'" << endl;
    if (unit == "F")
    {
        m_unit = F;
    }
    else
    {
        m_unit = C;
    }

    m_lowBound = strtod(lower.c_str(), 0);
    m_highBound = strtod(upper.c_str(), 0);
    m_period = strtod(period.c_str(), 0);

//    cout << "'" << m_unit << "' '" << m_lowBound << "' '" << m_highBound << "' '" << m_period << "'" << endl;
}

void* TemperatureSensor::Activity(void*)
{
    srand ( time ( NULL));
    double range = (m_highBound - m_lowBound); 
    double div = RAND_MAX / range;
    double temperature;
    std::ostringstream sstream;
    for(;;)
    {
        temperature = m_lowBound + (rand() / div);
        sstream << temperature;
//        cout << "Creatinr event with " << m_type << " " << m_room << " " << m_floor << " " << sstream.str() << endl;
        Event *e = new Event(m_type, m_room, m_floor, sstream.str());
 //       cout << "Event created " << e->Type() << " " << e->Room() << " " << e->Floor() << " " << e->Payload() << endl;
        sstream.str("");
        ShootEvent(e);
        sleep(m_period);
    }
    return NULL;
}

extern "C" string TypeName()
{
    return "ambient_temp";
}

extern "C" DeviceAgent* Creator(const string& _id)
{
    return new TemperatureSensor(_id);
}