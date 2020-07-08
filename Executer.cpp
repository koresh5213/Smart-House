#include "MainAPI.h"


using namespace std;

void AcceptKey(std::string& _line )
{
	if (_line == "sig1")
	{
		cout << "sendind sig " << SIGUSR2 <<endl;
		kill(0, SIGUSR2);
	}
}

int main(int argc, char* argv[])
{
	std::string cfgFile("./config.txt");
	if(argc > 1){
		cfgFile = argv[1];
	}

    MainAPI m(cfgFile);

	std::cout << "Running type q to quit\n";
	std::string cmd;
	do{
		std::cout << ">> ";
		std::cin >> cmd;
		AcceptKey(cmd);
	}while(cmd != "q");

}
