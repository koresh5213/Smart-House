#ifndef _DEVICE_AGENT_H
#define _DEVICE_AGENT_H

#include <stdexcept>    // for exception
#include <string>
#include <fstream>      

struct DeviceConfig
{
    std::string             m_id;
    std::string             m_type;
    std::string             m_room;
    int                     m_floor;
    std::string             m_log;
    std::string             m_configline;
    DeviceConfig(){};
};

//Abstract
class DeviceAgent
{
protected:
            DeviceAgent(const std::string& _id = "Unspecified");
            DeviceAgent(const std::string& _id, const std::string& _room, const int _floor, const std::string& _configline);
public:
            virtual ~DeviceAgent();
public:
    void                    SetDeviceParams(const std::string& _type, const std::string& _room, const int _floor, const std::string& _configline);
protected:
    virtual void            ParseConfigLine(const std::string&) throw (std::invalid_argument);
    void                    SetType(const std::string&);
private:
// Non copyable
            DeviceAgent(const DeviceAgent&);
    DeviceAgent& operator=(const DeviceAgent&);
protected:
// Function to fatch a value from configline
    std::string GetParameter(const std::string& _hay, const std::string& _needle);
protected:
    std::string             m_id;
    std::string             m_type;
    std::string             m_room;
    int                     m_floor;
    std::string             m_log;
private:
//    std::ofstream           m_outfile;
//    std::string             m_str;
public:
    virtual void            GetSignal();
protected:
    void                    WriteToFile(const std::string&);

};

#endif