#include "EventContainer.h"
#include <iostream>
using namespace std;

EventContainer::EventContainer(unsigned int _size)
: m_wq(_size)
{}

void EventContainer::RecieveEvent(Event* _event)
{
    m_wq.Enqueue(_event);
}

Event* EventContainer::WaitForEvent()
{
    Event temp;
    Event* eptr = &temp;
    m_wq.Dequeue(eptr);
    return eptr;
}

void EventContainer::PrintSize()
{
    cout << m_wq.Size() << endl;
}