#include "Agents/TemperatureSensor.h"
#include "Agents/HVACController.h"
#include "../EventContainer.h"
#include "../Broker.h"
#include "../EventSender.h"
#include "../SubscribeRegistry.h"
#include "AgentFactory.h"
#include "ConfigFileParser.h"
#include "MainAPI.h"

#include <iostream> // for debug
#include <unistd.h>  //Header file for sleep()
#include <vector>
using namespace std;

void nonAPITest()
{
    EventContainer container(1000);
    EventSender sender;
    SubscribeRegistry subreg;

    EventBroker broker(container, subreg, sender);

    AgentFactory factory(subreg, container);
    ConfigFileParser parser("./config.txt");

    vector<DeviceConfig> vec;
    parser.Parse(vec);


}

void APITest()
{
    MainAPI m;
    sleep(10);
}

int main()
{
    APITest();
    return 0;
}