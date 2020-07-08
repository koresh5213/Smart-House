#include "Agents/HVACController.h"
#include "Event.h"
#include <iostream>
#include <stdlib.h> // for strtod
using namespace std;

HVACController::HVACController(const std::string& _id, EventSubscriber* _subsctiber)
: ControllerAgent(_id, _subsctiber)
{
}

void HVACController::EventHandle(Event* _event)
{
    cout << "Event accepted in HVAC " << m_id << ": ";
    cout << "Time: " << _event->Time();
    cout << " Type: " << _event->Type();
    cout << " Room: " << _event->Room();
    cout << " Floor: " << _event->Floor();
    cout << " Payload: " << _event->Payload() << endl;
}

void HVACController::ParseConfigLine(const std::string& _line) throw (std::invalid_argument)
{
    string str = GetParameter(_line, "tmp:");
    m_temperature = strtod(str.c_str(), 0);
}

void HVACController::SubscriptionList()
{
    Subscribe("ambient_temp", m_room);
    Subscribe("abmient_temp", m_floor);
}

extern "C" string TypeName()
{
    return "HVACController";
}

extern "C" DeviceAgent* Creator(const string& _id)
{
    return new HVACController(_id);
}