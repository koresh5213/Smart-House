#ifndef _EVENT_H
#define _EVENT_H

#include <string>
#include <time.h>

class Event
{
public:
        Event();
        Event(const std::string& _type, const std::string& _room, 
        const int _floor, const std::string& _payload = "");
public:

    std::string     Time();
    std::string     Payload();
    std::string     Type();
    std::string     Room();
    int             Floor();
private:
    time_t          m_time;
    std::string     m_type;
    std::string     m_room;
    int             m_floor;
    std::string     m_payload; // TODO- maybe not a string?
};

#endif