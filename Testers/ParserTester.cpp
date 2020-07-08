#include "ConfigFileParser.h"
using namespace std;

int main()
{
    ConfigFileParser p("./config2.txt");
    vector <DeviceConfig> v;
    p.Parse(v);

    return 0;
}