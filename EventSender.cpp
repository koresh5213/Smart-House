#include "EventSender.h"
#include "Interfaces/IEventDestination.h"
#include <cstddef> // for NULL

void EventSender::PublishEvent(EventDestination* _dest, Event* _event)
{
    if (_dest == NULL)
    {
        return; // TODO- exception
    }
    _dest->AcceptEvent(_event);
}