#ifndef MAINAPI_H
#define MAINAPI_H

#include "EventContainer.h"
#include "EventSender.h"
#include "SubscribeRegistry.h"
#include "Broker.h"
#include "DeviceAgent.h"
#include "AgentFactory.h"
#include "ConfigFileParser.h"
#include "SensorAgent.h"
#include "ControllerAgent.h"
#include "Thread.h"
#include "SignalRegistry.h"

#include <map>
#include <set>
#include <string>

class MainAPI
{
public:
    MainAPI(std::string const&);
    ~MainAPI();
private:
    bool IsIDExist(const std::string&);
    void RunDevice(DeviceAgent* );
private:
    std::map<std::string, DeviceAgent*> m_agents;
    std::set<Thread*>                   m_sensors;
private:
    EventContainer      m_contatiner;
    EventSender         m_sender;
    SubscribeRegistry   m_subreg;

    EventBroker         m_broker;
    Thread*             m_brokerThread;

    ConfigFileParser    m_cfileParser;
    AgentFactory        m_factory;

    SignalRegistry      m_signalRegistry;
};

#endif