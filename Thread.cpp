#include "Thread.h"
#include <unistd.h> // for sleep
#include <iostream> // for debug

Runnable::~Runnable(){}

Thread::Thread(Runnable* _run, void* _arg)
{
    void* (*fun)(void*) = &(this->ThreadFunction);
    ThreadFunctionPackage *pack = new ThreadFunctionPackage;
    pack->m_runnable = _run;
    pack->m_arg = _arg;
    
    pthread_create(&m_pthread, NULL, fun, pack);
}

void* Thread::ThreadFunction(void* _arg)
{
    ThreadFunctionPackage* pack = static_cast<ThreadFunctionPackage*>(_arg);
    Runnable* runner =  pack->m_runnable;
    void* arg = (pack->m_arg);
    delete pack;
    runner->run(arg);
    return 0;
}

void Thread::Join(void** _retval)
{
    pthread_join(m_pthread, _retval);
}