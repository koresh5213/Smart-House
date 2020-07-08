#ifndef SEMAPHORE_H
#define SEMAPHORE_H

//#include <pthread.h>
#include <semaphore.h>

class Semaphore
{
public:
        Semaphore(unsigned int _cap = 0);
        ~Semaphore();

    void Wait();
    void Post();
private:
    // Prevent copy
    Semaphore(const Semaphore&);
    Semaphore& operator=(const Semaphore&);
private:
    sem_t m_sem; 
};

#endif