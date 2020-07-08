#include "WaitableQueue/WQueue.h"
#include <iostream>
using namespace std;

#include <unistd.h>  //Header file for sleep()
#include <pthread.h> 
#include <queue>

#include "Thread.h"

void* Insert(void* _payload)
{
    WQueue<int> *q;
    q = (WQueue<int>*)_payload;
    q->Enqueue(4);
    return NULL;
}

int Test1()
{
    WQueue<int> q(10);
    q.Enqueue(4);
    int res = 0;
    q.Dequeue(res);
    cout << res << endl;

    return 0;
}
  
class Inserter : public Runnable
{
public:
    void run(void* _in)
    {
            WQueue<int> *q;
            q = (WQueue<int>*)_in;
            for (int i = 0; i < 10; ++i)
            {
                    q->Enqueue(2*i);
                    cout << "Enqued " << 2*i << endl;
                    sleep(1);
            }
    }
};

class Remover : public Runnable
{
public:
    void run(void* _in)
    {
            WQueue<int> *q;
            q = (WQueue<int>*)_in;
            int res=0;
            for (;;)
            {
                    q->Dequeue(res);
                    cout << "Dequeued " << res << endl;
            }
    }
};


int ThreadTest()
{
    WQueue<int> q(10);
    Inserter in;
    Remover rem;
    Thread remvrthread(&rem, &q);
    sleep(3);
    Thread insthread(&in, &q);
    
    sleep(10);
    return 0;
}

int main()
{
    ThreadTest();
}