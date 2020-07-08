#include "MainAPI.h"
#include <vector>
using namespace std;

MainAPI::MainAPI(std::string const& cfgFile)
: m_contatiner(1000)
, m_sender()
, m_subreg()
, m_broker(m_contatiner, m_subreg, m_sender)
, m_cfileParser(cfgFile)
, m_factory(m_subreg, m_contatiner)
, m_signalRegistry()
{
    vector<DeviceConfig> vec;
    m_cfileParser.Parse(vec);

    vector<DeviceConfig>::iterator itr;
    vector<DeviceConfig>::iterator endItr = vec.end();
    DeviceAgent* tempAgent;

    for (itr = vec.begin(); itr != endItr; ++itr)
    {
        tempAgent = m_factory.CreateAgent(*itr);
        if (tempAgent == 0)
        {
            // throw exception
            continue;
        }

        if (IsIDExist(itr->m_id))
        {
            delete tempAgent;
            // throw exception
            continue;
        }
        m_agents.insert(pair<string, DeviceAgent*>(itr->m_id, tempAgent));
        RunDevice(tempAgent);
    }

    m_brokerThread = m_broker.RunBroker();
}

void MainAPI::RunDevice(DeviceAgent* _device)
{
    if (SensorAgent* s = dynamic_cast<SensorAgent*>(_device))
    {
        Thread* thread = s->RunSensor();
        if (thread != 0)
        {
            m_sensors.insert(thread);
        }
    }

    if (ControllerAgent* c = dynamic_cast<ControllerAgent*>(_device))
    {
        c->SetSubscriber(m_subreg);
    }

    if (SigHandler* h = dynamic_cast<SigHandler*>(_device))
    {
        h->SetSubscriber(&m_signalRegistry);
        cout << "signal registry set" << endl;
    }
}

bool MainAPI::IsIDExist(const string& _id)
{
    return (m_agents.find(_id) != m_agents.end());
}

MainAPI::~MainAPI()
{
    map<std::string, DeviceAgent*>::iterator itr, endItr;
    endItr = m_agents.end();
    for (itr = m_agents.begin(); itr != endItr; ++itr)
    {
        delete itr->second;
    }

    std::set<Thread*>::iterator tItr, tEndItr;
    tEndItr = m_sensors.end();
    for (tItr = m_sensors.begin(); tItr != tEndItr; ++tItr)
    {
        delete *tItr;
    }
    delete m_brokerThread;
}
