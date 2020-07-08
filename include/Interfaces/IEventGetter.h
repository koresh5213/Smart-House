#ifndef EVENT_GETTER
#define EVENT_GETTER

class Event;

// Interface
class EventGetter
{
public:
    virtual Event* WaitForEvent()=0;
    virtual ~EventGetter(){};
};

#endif