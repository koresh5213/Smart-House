#include "WaitableQueue/Mutex.h" 
#include <stdexcept>    // For runtime exception

Mutex::Mutex()
{
    int res = pthread_mutex_init(&m_mutex, NULL);
    if (res != 0)
    {
        throw std::runtime_error("Fail at mutex init");
    }
}

Mutex::~Mutex()
{
    pthread_mutex_destroy(&m_mutex);
}

void Mutex::Lock()
{
    int res = pthread_mutex_lock(&m_mutex);
    if (res != 0)
    {
        throw std::runtime_error("Fail in mutex lock");
    }
}

void Mutex::Unlock()
{
    int res = pthread_mutex_unlock(&m_mutex);
    if (res != 0)
    {
        throw std::runtime_error("Fail at mutex unlock");
    }
}