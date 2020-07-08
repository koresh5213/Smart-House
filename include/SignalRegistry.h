#ifndef SIGNAL_REGISTRY_H
#define SIGNAL_REGISTRY_H


#include <signal.h>
#include <cstring>  // for memset
#include <map>
#include <utility> // for pair

class SignalRegistry;

//	Abstract
class SigHandler {
public:
	virtual ~SigHandler() {};
	virtual void HandleSignal() = 0;

	void SetSubscriber(SignalRegistry*);
protected:
	virtual void SignalSubscribeList();
	void SubscribeToSignal(int _signum);
private:
	SignalRegistry*		m_registry;
};

class SignalRegistry
{
public:
	SignalRegistry();
	static void SubscribeToSignal(int _signum, SigHandler* _handler);

public:
    static void CatcherFunc(int _signum, siginfo_t* _siginfo, void* _context);

private: 
	static std::map<int, SigHandler*>		m_handlers;
};


#endif
