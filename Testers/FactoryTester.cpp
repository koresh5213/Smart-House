#include "AgentFactory.h"
#include "ConfigFileParser.h"
#include <iostream>

using namespace std;

int main()
{
    AgentFactory f;
    ConfigFileParser parser("./config.txt");

    vector<DeviceConfig> v;

    parser.Parse(v);

    DeviceAgent* de = f.CreateAgent(v[0]);
    cout << de << endl;
    
    return 0; 
}