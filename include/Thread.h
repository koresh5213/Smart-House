#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>

class Runnable {
public:
	virtual ~Runnable();
	virtual void run(void*) =0;
};

struct ThreadFunctionPackage
{
    Runnable*   m_runnable;
    void*       m_arg;
};

class Thread
{
public:
    Thread(Runnable*, void* _arg = NULL);
    void            Join(void** _retnal=NULL);
private:
//  Prevent copies
    Thread(const Thread&);
    Thread& operator=(const Thread&);
private:
    static void*    ThreadFunction(void*);
    pthread_t       m_pthread;
};


#endif