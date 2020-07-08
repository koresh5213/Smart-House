#include "SignalRegistry.h"
#include <string>
#include <iostream>

using namespace std;

std::map<int, SigHandler*> SignalRegistry::m_handlers;

void SigHandler::SetSubscriber(SignalRegistry* _reg)
{
	if (_reg == 0)
	{
		cout << "trying to set subscriber is null" << endl;
		return;
	}
	m_registry = _reg;
	SignalSubscribeList();
}

void SigHandler::SignalSubscribeList()
{
}

void SigHandler::SubscribeToSignal(int _signum)
{
	SignalRegistry::SubscribeToSignal(_signum, this);
	// if (m_registry == 0)
	// {
	// 	cout << "m_registry is null" << endl;
	// 	return;
	// }
	// m_registry->SubscribeToSignal(_signum, this);
}


//////////////////////


SignalRegistry::SignalRegistry()
{
    
}

void SignalRegistry::SubscribeToSignal(int _signum, SigHandler* _handler)
{
	struct sigaction m_sigaction;
	memset(&m_sigaction, 0, sizeof(m_sigaction));

    m_sigaction.sa_sigaction = &CatcherFunc;
    m_sigaction.sa_flags = SA_SIGINFO;

	if(_handler==0) return;
	std::map<int, SigHandler*>& map = SignalRegistry::m_handlers;
    if (map.find(_signum) != map.end())
    {
		cout << "signum already taken" << endl;
        return;
    }

    map[_signum] = _handler;
	cout << "after insrtion, size " << m_handlers.size() << " and signum = " << m_handlers.find(_signum)->first <<endl;

    sigaction(_signum, &m_sigaction, 0);
}

void SignalRegistry::CatcherFunc(int _signum, siginfo_t* _siginfo, void* _context)
{
	cout << "catched" << endl;
	std::map<int, SigHandler*>::iterator itr = SignalRegistry::m_handlers.find(_signum);

	if ( itr == m_handlers.end() )
	{
		// Throw signal again
		cout << "didnt find it " << m_handlers.size() <<endl;
		return;
	}
	SigHandler* handler = itr->second;
	try{
		handler->HandleSignal();
	}catch(...){}
}