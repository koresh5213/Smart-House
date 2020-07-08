#include "SignalRegistry.h"
#include <iostream>

using namespace std;

class SimpleSigHandler : public SigHandler
{
public:
    virtual void HandleSignal()
    {
        cout << "Got it" << endl;
    }
    virtual void SignalSubscribeList()
    {
        SubscribeToSignal(SIGUSR1);
    }
};

void Test()
{
    SimpleSigHandler h1;
    SimpleSigHandler h2;

    SignalRegistry r;

    h1.SetSubscriber(&r);

    raise(SIGUSR1);
    raise(SIGUSR2);

}

int main()
{
    Test();


    return 0;
}