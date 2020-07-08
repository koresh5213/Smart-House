#ifndef AGENTFACTORY_H
#define AGENTFACTORY_H

#include "DeviceAgent.h"
#include "Interfaces/IEventSubscriber.h"
#include "Interfaces/IEventReciever.h"

#include <string>
#include <map>
#include <vector>

class AgentFactory
{
typedef DeviceAgent* (*CreatorFunc)(const std::string&);
typedef std::string (*TypenameFunc)();

public:
        AgentFactory(EventSubscriber& _subscriber, EventReciever& _reciever, const std::string& _agentsPath = "./Agents/");

    ~AgentFactory();
    
    DeviceAgent*    CreateAgent(DeviceConfig&);

private:
// Prevent copy
    AgentFactory(const AgentFactory&);
    AgentFactory& operator=(const AgentFactory&);

private:
    std::map<std::string, CreatorFunc>      m_creators;

private:
    DeviceAgent*    CreateAgent(const std::string& _type, const std::string& _id);

    void ReadDirectory(std::vector<std::string>& v);
    void ReadFromDir();

    CreatorFunc GetCreatorFunction(void* _handler);
    TypenameFunc GetTypeFunction(void* _handler);
    
    std::string                             m_directory;
    std::string                             m_ctorFuncName;
    std::string                             m_typeFuncName;
    
    EventSubscriber&    m_subscriber;
    EventReciever&      m_reciever;

    void*               m_handler; // saving it to close at destruct
};

#endif