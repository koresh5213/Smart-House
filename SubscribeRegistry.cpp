#include "SubscribeRegistry.h"
#include <iostream>
using namespace std;

void SubscribeRegistry::Subscribe(EventDestination* _destination, const std::string& _type, const std::string& _room)
{
    RoomEvent re(_type, _room);
    Controllers& des = m_roomMap[re];
    des.insert(_destination);
}

void SubscribeRegistry::Unsubscribe(EventDestination* _destination, const std::string& _type, const std::string& _room)
{
    RoomEvent re(_type, _room);
    Controllers& des = m_roomMap[re];
    des.erase(_destination);
}

void SubscribeRegistry::Subscribe(EventDestination* _destination, const std::string& _type, const int _floor)
{
    FloorEvent fe(_type, _floor);
    Controllers& des = m_floorMap[fe];
    des.insert(_destination);
}

void SubscribeRegistry::Unsubscribe(EventDestination* _destination, const std::string& _type, const int _floor)
{
    FloorEvent fe(_type, _floor);
    Controllers& des = m_floorMap[fe];
    des.erase(_destination);
}

std::set<EventDestination*> SubscribeRegistry::FindSubscribers(const std::string& _type, const std::string& _room)
{
    RoomEvent re(_type, _room);
    
    return m_roomMap[re];
}

std::set<EventDestination*> SubscribeRegistry::FindSubscribers(const std::string& _type, const int _floor)
{
    FloorEvent fe(_type, _floor);
    return m_floorMap[fe];
}