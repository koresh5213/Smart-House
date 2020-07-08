#include "Agents/TemperatureSensor.h"
#include "Agents/HVACController.h"
#include "../EventContainer.h"
#include "../Broker.h"
#include "../EventSender.h"
#include "../SubscribeRegistry.h"
#include "Thread.h"
#include <iostream> // for debug
#include <unistd.h>  //Header file for sleep()
using namespace std;

void Subscription()
{
    EventContainer container(1000);
    EventSender sender;
    SubscribeRegistry subreg;
    EventBroker broker(&container, &subreg, &sender);

    // Sensors
    TemperatureSensor s1(&container);
    TemperatureSensor s2(&container);
    TemperatureSensor s3(&container);

    s1.SetDeviceParams("typeA", "roomA", 3, "units: F; lower: -55; upper: -5; period: 1.5");
    s2.SetDeviceParams("typeA", "roomB", 4, "units: F; lower: -5; upper: 25; period: 1.1");
    s3.SetDeviceParams("typeA", "roomC", 5, "units: F; lower: 25; upper: 55; period: 0.7");
    
    //Controllers
    HVACController c1;
    HVACController c2;
    HVACController c3;
    
    subreg.Subscribe(&c1, "typeA", "roomA");
    subreg.Subscribe(&c2, "typeA", "roomB");
    subreg.Subscribe(&c3, "typeA", 5);
    
    broker.RunBroker();

    s1.RunSensor();
    s2.RunSensor();
    s3.RunSensor();
    

    sleep(4);
}

int main()
{
    Subscription();
}