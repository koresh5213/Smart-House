#ifndef IEVENT_RECIEVER_H
#define IEVENT_RECIEVER_H

class Event;

// Interface
class EventReciever
{
public:
    virtual void RecieveEvent(Event*)=0;
    virtual ~EventReciever(){};
};

#endif 