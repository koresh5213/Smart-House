#include "AgentFactory.h"
#include "ControllerAgent.h"
#include "SensorAgent.h"

#include <dirent.h>   // 'DIR'
#include <dlfcn.h>      //for 'opendir'
#include <cstdio>      //for stderr
#include <algorithm>  //for 'find()'
#include <iostream>  //for debug
#include <errno.h>  // errno
#include <string.h> // also errno

using namespace std;
 
AgentFactory::AgentFactory(EventSubscriber& _subscriber, EventReciever& _reciever, const std::string& _agentsPath)
: m_directory(_agentsPath)
, m_subscriber(_subscriber)
, m_reciever(_reciever)
{
    // TODO: make sure last charecter of directory is '/' !
    m_ctorFuncName = "Creator";
    m_typeFuncName = "TypeName";

    ReadFromDir();
}

AgentFactory::~AgentFactory()
{
    if (m_handler != 0)
    {
        dlclose(m_handler);
    }
}

void AgentFactory::ReadDirectory(vector<string>& v)
{
    DIR* dirp = opendir(m_directory.c_str());

    if (dirp == 0)
    {
        printf("Agents directory not found %s\n", strerror(errno));
        return;
    }

    string temp;

    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) 
    {
        temp = (dp->d_name);

        // Take only .so files
        if ( string::npos != temp.find(".so") )
        {
            temp = m_directory + temp;
            v.push_back(temp);
        }
    }
    closedir(dirp);
}

typename AgentFactory::CreatorFunc AgentFactory::GetCreatorFunction(void* _handler)
{
    return (CreatorFunc)dlsym(_handler, m_ctorFuncName.c_str());
}

typename AgentFactory::TypenameFunc AgentFactory::GetTypeFunction(void* _handler)
{
    return (TypenameFunc)dlsym(_handler, m_typeFuncName.c_str());
}

void AgentFactory::ReadFromDir()
{
    vector<string> files;
    ReadDirectory(files);

    vector<string>::iterator itr = files.begin();
    vector<string>::iterator enditr = files.end();

    void* handler;
    string tempStr;
    TypenameFunc typefunc;
    CreatorFunc creatorfunc;
    
    for(;itr!=enditr; ++itr)
    {
        handler = dlopen(itr->c_str(), RTLD_LAZY);
        if (!handler)
        {
            fprintf(stderr, "Error dlopen: %s\n", dlerror()); // TODO: put error to command line
            continue;
        }

        typefunc = GetTypeFunction(handler);
        if (typefunc == NULL)
        {
            cout << "type Function not found" << endl;
            continue;
        }

        tempStr = typefunc();

        // check if type name exist
        if (m_creators.find(tempStr) != m_creators.end())
        {
            cout << "Conflicting type names in .so folder: " << tempStr <<endl;
            continue;
        }

        creatorfunc = GetCreatorFunction(handler);

        m_creators.insert(std::pair<string,CreatorFunc>(tempStr, creatorfunc) );
    }
    m_handler = handler;
}

DeviceAgent* AgentFactory::CreateAgent(const std::string& _type, const std::string& _id)
{
    std::map<std::string, CreatorFunc>::iterator finderItr;

    finderItr = m_creators.find(_type);

    if (finderItr == m_creators.end())
    {
        cout << "Agent not found: " << _type << endl;
        return 0;
    }

    CreatorFunc func = finderItr->second;

    return func(_id);
}

DeviceAgent* AgentFactory::CreateAgent(DeviceConfig& _config)
{
    DeviceAgent* ans = CreateAgent(_config.m_type, _config.m_id);

    if (ans == 0)
    {
        return 0;
    }

    ans->SetDeviceParams(_config.m_type, _config.m_room, _config.m_floor, _config.m_configline);

    if (ControllerAgent* c = dynamic_cast<ControllerAgent*>(ans))
    {
        c->SetSubscriber(m_subscriber);
    }

    if (SensorAgent* s = dynamic_cast<SensorAgent*>(ans))
    {
        s->SetReciever(&m_reciever);
    }

    return ans;
}