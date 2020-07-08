#ifndef _IDEVICE_FINDER_H
#define _IDEVICE_FINDER_H

#include <set>
#include <string>

class EventDestination;

//Interface
class DeviceFinder
{
public:
    virtual std::set<EventDestination*>    FindSubscribers(const std::string& _type, const std::string& _room)=0;
    virtual std::set<EventDestination*>    FindSubscribers(const std::string& _type, const int floor)=0;

    virtual ~DeviceFinder(){}; 
};

#endif