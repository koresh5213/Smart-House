#include "WaitableQueue/Semaphore.h"
#include <errno.h>      
#include <stdexcept>    // For runtime exception
#include <semaphore.h>

Semaphore::Semaphore(unsigned int _cap)
{
    int res = sem_init(&m_sem, 0, _cap);
    if (res != 0)
    {
        throw std::runtime_error("Fail at sem init");
    }
}

Semaphore::~Semaphore()
{
    sem_destroy(&m_sem);
}

void Semaphore::Wait()
{
    int res;
    do
    {
        res = sem_wait(&m_sem);
    } while (res !=0 && errno == EINTR);
    if (res != 0)
    {
        throw std::runtime_error("Fail at sem wait");
    }
}

void Semaphore::Post()
{
    int res = sem_post(&m_sem);
    if (res != 0)
    {
        throw std::runtime_error("Fail at sem post");
    }
}