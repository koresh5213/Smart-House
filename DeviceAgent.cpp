#include "DeviceAgent.h"
#include <algorithm> //for remove_if

using namespace std;

DeviceAgent::DeviceAgent(const std::string& _id)
: m_id(_id)
, m_type("unspecified")
, m_room("unspecified")
, m_floor(0)
{}

DeviceAgent::DeviceAgent(const std::string& _id, const std::string& _room, const int _floor, const std::string& _configline)
: m_id(_id)
, m_room(_room)
, m_floor(_floor)
{
    ParseConfigLine(_configline);
}

DeviceAgent::~DeviceAgent(){}

void DeviceAgent::ParseConfigLine(const string&)throw (std::invalid_argument) {}

void DeviceAgent::SetDeviceParams(const std::string& _type, const std::string& _room, 
            const int _floor, const std::string& _configline)
{
    m_type = _type;
    m_room=_room;
    m_floor=_floor;
    ParseConfigLine(_configline);
}

string DeviceAgent::GetParameter(const std::string& _hay, const string& _needle)
{
    size_t beginIndex = _hay.find(_needle);
    if (beginIndex == string::npos)
    {
        throw std::invalid_argument("Error in config line parse");
    }
    beginIndex += _needle.length();

    size_t endIndex = _hay.find(';', beginIndex);  //TODO- switch hardcoded ':' to be parameterized
    if (endIndex == string::npos)
    {
        endIndex = _hay.length();
    }

    string answer =  _hay.substr(beginIndex, endIndex-beginIndex);
    // Erasing whitepaces
    answer.erase(std::remove_if(answer.begin(), answer.end(), ::isspace), answer.end());

    return answer;
}

void DeviceAgent::SetType(const std::string& _type)
{
    m_type = _type;
}

void DeviceAgent::GetSignal(){}

/*
void DeviceAgent::SetOutputMode(bool)
{

}
void DeviceAgent::WriteToFile(const std::string&)
{

}
*/