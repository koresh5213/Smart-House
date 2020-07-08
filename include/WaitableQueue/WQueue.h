#ifndef _WAITABLE_QUEUE_H
#define _WAITABLE_QUEUE_H

#include "WaitableQueue/Mutex.h"
#include "WaitableQueue/Semaphore.h"
#include <queue>
#include <iostream> // for debug

template <class T>
class WQueue
{
public:
    WQueue(unsigned int _size = 0);
    //~WQueue();
public:
    void            Dequeue(T&);
    void            Enqueue(const T&);
    inline bool     IsEmpty()const;
    size_t          Size()const;
private:
    // Prevent Copy
    WQueue(const WQueue&);
    WQueue& operator=(const WQueue&);
private:
    std::queue<T>       m_queue;
    Mutex               m_mutex;
    Semaphore           m_empty;
    Semaphore           m_full;
};

template <class T>
WQueue<T>::WQueue(unsigned int _size)
: m_empty(_size)
, m_full(0)
{
}

template <class T>
bool WQueue<T>::IsEmpty()const
{
    return m_queue.empty();
}

template <class T>
size_t WQueue<T>::Size()const
{
    return m_queue.size();
}

template <class T>
void WQueue<T>::Enqueue(const T& _in)
{
    m_empty.Wait();
    m_mutex.Lock();
    
    try
    {
        m_queue.push(_in);
    }
    catch(...)
    {
        m_mutex.Unlock();
        throw;
    }
    
    m_full.Post();
    m_mutex.Unlock();
}   

template <class T>
void WQueue<T>::Dequeue(T& _in)
{
    m_full.Wait();
    m_mutex.Lock();

    try
    {
        _in = m_queue.front();
        m_queue.pop();
    }
    catch(const std::exception& e)
    {
        m_empty.Post();
        m_mutex.Unlock();
        throw;
    }
    
    m_empty.Post();
    m_mutex.Unlock();
}

#endif