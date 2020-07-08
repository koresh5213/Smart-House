#include "Agents/TemperatureSensor.h"
#include "Agents/HVACController.h"
#include "../EventContainer.h"
#include "../Broker.h"
#include "../EventSender.h"
#include "../SubscribeRegistry.h"
#include <iostream> // for debug
#include <unistd.h>  //Header file for sleep()
using namespace std;

int SensorTest(void)
{
    EventContainer container(1000);
    EventBroker broker(&container, NULL, NULL);
    TemperatureSensor sensor(&container);

    sensor.ParseConfigLine("units: F; lower: -55; upper: 55; period: 2.5");
    sensor.RunSensor(NULL);
    broker.RunBroker();
    

    sleep(10);
    return 0;
}

int SubregTest(void)
{
    SubscribeRegistry subreg;
    HVACController sensor1;
    HVACController sensor2;

    set<EventDestination*> temp;
    
    subreg.Subscribe(&sensor1, "abc", 12);
    subreg.Subscribe(&sensor1, "abc", "bcd");

    temp = subreg.FindSubscribers("abc", 12);
    temp = subreg.FindSubscribers("abc", 13);
    temp = subreg.FindSubscribers("abc", "bcd");
    

    return 0;
}

int WholeTest(void)
{
    EventContainer container(1000);
    EventSender sender;
    SubscribeRegistry subreg;

    EventBroker broker(&container, &subreg, &sender);

    TemperatureSensor sensor(&container);
    sensor.SetDeviceParams("temp", "bcs", 3, "units: F; lower: -55; upper: 55; period: 1.5");

    HVACController controller;
    subreg.Subscribe(&controller, "temp", 3);

    sensor.RunSensor(NULL);
    broker.RunBroker();

    sleep(10);
    return 0;
}

int main(void)
{
    WholeTest();
    return 0;
}