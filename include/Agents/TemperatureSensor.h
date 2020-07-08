#ifndef _TEMPERATURESENSOR_H
#define _TEMPERATURESENSOR_H

#include "SensorAgent.h"
class EventReciever;
 
class TemperatureSensor : public SensorAgent
{
typedef enum TempUnit_t {C, F} TempUnit;

public:
    TemperatureSensor(const std::string&);  
    virtual void        ParseConfigLine(const std::string&)throw (std::invalid_argument); // TODO: private?
protected:
//    void                ShootEvent(Event*);
private:
    virtual void*       Activity(void*);
private:
    TempUnit            m_unit;
    double              m_lowBound;
    double              m_highBound;
    double              m_period;
};
//

#endif