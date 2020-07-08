#ifndef _MUTEX_H
#define _MUTEX_H

#include <pthread.h>

class Mutex
{
public:
        Mutex();
        ~Mutex();
public:
    void        Lock();
    void        Unlock();
private:
    // Prevent copy
    Mutex(const Mutex&);
    Mutex& operator= (const Mutex&);
private:
    pthread_mutex_t m_mutex;
};

#endif