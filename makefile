CC=g++
HEADERFOLDER= ./include
CPPFOLDER= .
CPPFLAGS= -I $(HEADERFOLDER) -I $(HEADERFOLDER)/Agents -pthread -ldl
CXXFLAGS= -g -ansi -pedantic -Wall -Werror -std=c++03 
LDFLAGS=  -lm -lrt -lpthread -ldl 

Executer: Executer.cpp MainAPI.o EventContainer.o EventSender.o SubscribeRegistry.o Broker.o DeviceAgent.o AgentFactory.o ConfigFileParser.o SensorAgent.o ControllerAgent.o Thread.o WaitableQueue/Semaphore.o WaitableQueue/Mutex.o Event.o SignalRegistry.o
	$(CC) $(CPPFLAGS) $(CXXFLAGS) Executer.cpp MainAPI.o EventContainer.o EventSender.o SubscribeRegistry.o Broker.o DeviceAgent.o AgentFactory.o ConfigFileParser.o SensorAgent.o ControllerAgent.o Thread.o WaitableQueue/Semaphore.o WaitableQueue/Mutex.o Event.o SignalRegistry.o -o Executer -ldl

MainAPI.o:  $(HEADERFOLDER)/MainAPI.h MainAPI.cpp EventContainer.o EventSender.o SubscribeRegistry.o Broker.o DeviceAgent.o AgentFactory.o ConfigFileParser.o SensorAgent.o ControllerAgent.o Thread.o

DeviceAgent.o: $(HEADERFOLDER)/DeviceAgent.h DeviceAgent.cpp

Thread.o: $(HEADERFOLDER)/Thread.h Thread.cpp 

WaitableQueue/Mutex.o: $(HEADERFOLDER)/WaitableQueue/Mutex.h WaitableQueue/Mutex.cpp

WaitableQueue/Semaphore.o: $(HEADERFOLDER)/WaitableQueue/Semaphore.h WaitableQueue/Semaphore.cpp

SensorAgent.o: $(HEADERFOLDER)/SensorAgent.h SensorAgent.cpp DeviceAgent.o Thread.o

Event.o: $(HEADERFOLDER)/Event.h Event.cpp 

EventSender.o: $(HEADERFOLDER)/EventSender.h EventSender.cpp

ControllerAgent.o: $(HEADERFOLDER)/ControllerAgent.h ControllerAgent.cpp 

EventContainer.o: $(HEADERFOLDER)/EventContainer.h EventContainer.cpp $(HEADERFOLDER)/Interfaces/IEventReciever.h Thread.o WaitableQueue/Mutex.o WaitableQueue/Semaphore.o Event.o

SubscribeRegistry.o: $(HEADERFOLDER)/SubscribeRegistry.h SubscribeRegistry.cpp $(HEADERFOLDER)/Interfaces/IDeviceFinder.h $(HEADERFOLDER)/Interfaces/IEventSubscriber.h

WQueue.o: $(HEADERFOLDER)/WaitableQueue/WQueue.h WaitableQueue/Mutex.o WaitableQueue/Semaphore.o

Broker.o: $(HEADERFOLDER)/Broker.h Broker.cpp Thread.o Event.o

WaitableQueue/QTest: WaitableQueue/QTest.cpp WaitableQueue/Mutex.o WaitableQueue/Semaphore.o Thread.o include/WaitableQueue/WQueue.h

AgentFactory.o : $(HEADERFOLDER)/AgentFactory.h AgentFactory.cpp

ConfigFileParser.o: $(HEADERFOLDER)/ConfigFileParser.h  ConfigFileParser.cpp 

SignalRegistry.o: $(HEADERFOLDER)/SignalRegistry.h SignalRegistry.cpp 

#########
#Testers#
#########

Testers/UnitTest: Testers/UnitTester.cpp Agents/TemperatureSensor.cpp Agents/HVACController.cpp DeviceAgent.cpp SensorAgent.cpp Thread.cpp WaitableQueue/Mutex.cpp WaitableQueue/Semaphore.cpp Event.cpp EventContainer.cpp Broker.cpp Agents/HVACController.cpp EventSender.cpp SubscribeRegistry.cpp 
	$(CC) $(CPPFLAGS) $(CXXFLAGS) Testers/UnitTester.cpp Agents/TemperatureSensor.cpp Agents/HVACController.cpp DeviceAgent.cpp SensorAgent.cpp Thread.cpp WaitableQueue/Mutex.cpp WaitableQueue/Semaphore.cpp Event.cpp EventContainer.cpp Broker.cpp EventSender.cpp SubscribeRegistry.cpp -o Testers/UnitTest.o

Testers/APITester: Testers/APITester.cpp MainAPI.cpp AgentFactory.cpp ConfigFileParser.cpp $(HEADERFOLDER)/AgentFactory.h $(HEADERFOLDER)/ConfigFileParser.h DeviceAgent.cpp Broker.o SubscribeRegistry.cpp ControllerAgent.cpp
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -o Testers/APITester Testers/APITester.cpp AgentFactory.cpp ConfigFileParser.cpp DeviceAgent.cpp ControllerAgent.cpp WaitableQueue/Semaphore.cpp WaitableQueue/Mutex.cpp SubscribeRegistry.cpp EventContainer.cpp EventSender.cpp Broker.cpp Event.cpp Thread.cpp MainAPI.cpp SensorAgent.cpp -ldl 

Testers/FactoryTester : Testers/FactoryTester.cpp AgentFactory.cpp ConfigFileParser.cpp $(HEADERFOLDER)/AgentFactory.h $(HEADERFOLDER)/ConfigFileParser.h DeviceAgent.cpp
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -o Testers/FactoryTester Testers/FactoryTester.cpp AgentFactory.cpp ConfigFileParser.cpp DeviceAgent.cpp -ldl 

Testers/TemperatureTester: Agents/TemperatureTester.cpp Agents/TemperatureSensor
	$(CC) $(CPPFLAGS) $(CXXFLAGS) Agents/TemperatureTester.cpp Agents/TemperatureSensor.cpp DeviceAgent.cpp SensorAgent.cpp Thread.cpp WaitableQueue/Mutex.cpp WaitableQueue/Semaphore.cpp Event.cpp EventContainer.cpp Broker.cpp Agents/HVACController.cpp EventSender.cpp SubscribeRegistry.cpp -o Agents/TemperatureTester.o

Testers/ParserTester: Testers/ParserTester.cpp ConfigFileParser.o DeviceAgent.o

Testers/SignalsTester: Testers/SignalsTester.cpp SignalRegistry.o

########
#Agents#
########

Agents/TemperatureSensor: Agents/TemperatureSensor.cpp $(HEADERFOLDER)/Agents/TemperatureSensor.h DeviceAgent.o SensorAgent.o Thread.o
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -c Agents/TemperatureSensor.cpp DeviceAgent.cpp SensorAgent.cpp Thread.cpp

Agents/TemperatureSensor.so: Agents/TemperatureSensor.cpp $(HEADERFOLDER)/Agents/TemperatureSensor.h DeviceAgent.o SensorAgent.o Thread.o
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -shared -fPIC -o Agents/TemperatureSensor.so Agents/TemperatureSensor.cpp DeviceAgent.cpp SensorAgent.cpp Thread.cpp Event.cpp 

Agents/HVACController.so: Agents/HVACController.cpp $(HEADERFOLDER)/Agents/HVACController.h DeviceAgent.o SensorAgent.o Thread.o
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -shared -fPIC -o Agents/HVACController.so Agents/HVACController.cpp DeviceAgent.cpp ControllerAgent.cpp Thread.cpp Event.cpp -pthread

Agents/HVACController.o: $(HEADERFOLDER)/Agents/HVACController.h $(HEADERFOLDER)/Interfaces/IEventDestination.h $(CPPFOLDER)/Agents/HVACController.cpp

Agents/FireSafetySensor.o: $(HEADERFOLDER)/Agents/FireSafetySensor.h Agents/FireSafetySensor.cpp DeviceAgent.o

Agents/FireSafetySensor.so: $(HEADERFOLDER)/Agents/FireSafetySensor.h Agents/FireSafetySensor.cpp DeviceAgent.o SensorAgent.o SignalRegistry.o
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -shared -fPIC -o Agents/FireSafetySensor.so Agents/FireSafetySensor.cpp DeviceAgent.cpp SensorAgent.cpp SignalRegistry.cpp Thread.cpp Event.cpp -pthread

clean:
	rm -f *.out *.o */*.o /*/*.hgc