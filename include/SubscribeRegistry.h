#ifndef _SUBSCRIBE_REGISTRY_H
#define _SUBSCRIBE_REGISTRY_H

#include "Interfaces/IDeviceFinder.h"
#include "Interfaces/IEventSubscriber.h"
#include <map>
#include <set>
#include <vector>

class EventSource;
class EventDestination;
class DeviceAgent;

class SubscribeRegistry : public DeviceFinder, public EventSubscriber
{

typedef std::pair<std::string,std::string> RoomEvent;
typedef std::pair<std::string,int> FloorEvent;
typedef std::set<EventDestination*> Controllers;

public:
//      SubscribeRegistry();
//      ~SubscribeRegistry();

public:
// Device finder:
    virtual std::set<EventDestination*>    FindSubscribers(const std::string& _type, const std::string& _room);
    virtual std::set<EventDestination*>    FindSubscribers(const std::string& _type, const int floor);

public:
// Event subscriber:
    virtual void Subscribe(EventDestination*, const std::string& _type, const std::string& _room);
    virtual void Subscribe(EventDestination*, const std::string& _type, const int _floor);

    virtual void Unsubscribe(EventDestination*, const std::string& _type, const std::string& _room);
    virtual void Unsubscribe(EventDestination*, const std::string& _type, const int _floor);

private:
    std::map<RoomEvent, Controllers>        m_roomMap;
    std::map<FloorEvent, Controllers>       m_floorMap;

    
};
#endif