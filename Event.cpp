#include "Event.h"
#include <ctime>
#include <string>

Event::Event()
{}

Event::Event(const std::string& _type, const std::string& _room, 
const int _floor, const std::string& _payload)
: m_time(time(NULL))
, m_type(_type)
, m_room(_room)
, m_floor(_floor)
, m_payload(_payload)
{
}

std::string Event::Type()
{
    return m_type;
}

std::string Event::Room()
{
    return m_room;
}

int Event::Floor()
{
    return m_floor;
}

std::string Event::Payload()
{
    return m_payload;
}

std::string Event::Time()
{
    char buffer[32];
    struct tm* globaltime = gmtime(&m_time);
    strftime(buffer, 32, "%a, %d.%m.%Y %H:%M:%S", globaltime);
    
    return buffer;
}