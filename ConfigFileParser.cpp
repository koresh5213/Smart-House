#include "ConfigFileParser.h"

#include <stdio.h> // for sscanf
#include <cstring> // strlen, strcpy
#include <fstream>  // file stream
#include <iostream> // for debug
#include <algorithm> // for parsing

using namespace std;

ConfigFileParser::ConfigFileParser(const std::string& _path)
: m_path(_path)
{

}

bool ConfigFileParser::HasOnlySpaces(const std::string& str) 
{
   return str.find_first_not_of (' ') == str.npos;
}

ConfigFileParser::LineInfo ConfigFileParser::ParseLine(const std::string& _line)
{
    LineInfo info;

    info.m_type = ERROR;

//    cout << "Parsing line '" << _line << "': ";

    do
    {
        if (HasOnlySpaces(_line))
        {
            info.m_type = EMPTY;
            break;
        }
        if ( string::npos != _line.find("[") && string::npos !=  _line.find("]"))
        {
            info.m_type = ID;
            info.m_value = _line.substr(2, _line.size() - 3);
            break;
        }

        if ( string::npos !=  _line.find("type = ")  )
        {
            info.m_type = TYPE;
            info.m_value = _line.substr(strlen("type = "));
            break;
        }

        if ( string::npos != _line.find("room = ") ) 
        {
            info.m_type = ROOM;
            info.m_value = _line.substr(strlen("room = "));
            break;
        }

        if ( string::npos !=  _line.find("floor = ") ) 
        {
            info.m_type = FLOOR;
            info.m_value = _line.substr(strlen("floor = "));
            break;
        }

        if ( string::npos !=  _line.find("log = ") ) 
        {
            info.m_type = LOG;
            info.m_value = _line.substr(strlen("log = "));
            break;
        }

        if ( string::npos != _line.find("config = ") ) 
        {
            info.m_type = CONFIGLINE;
            info.m_value = _line.substr(strlen("config = "));
            break;
        }
    }
    while(false);
 //   cout << ": Returning " << info.m_type << " and " << info.m_value << endl;
    return info;
}

void ConfigFileParser::Parse(std::vector<DeviceConfig>& _vec) throw(std::runtime_error)
{
    ifstream ifs (m_path.c_str(), std::ifstream::in);
    string line;

    if (!ifs.is_open())
    {
        throw(std::runtime_error("Cannot open config file"));
    }

    while (!ifs.eof())
    {
        struct DeviceConfig dc;
        LineInfo lineinfo;
        bool id=false, type=false, room=false, floor=false, log=false, config=false;

        while(getline(ifs, line))
        {
            lineinfo = ParseLine(line);

            switch (lineinfo.m_type)
            {
                case ERROR:
                    throw(std::runtime_error("Config file format error"));
                break;
                case EMPTY:
                    continue;
                break;
                case ID:
                    id = true;
                    dc.m_id = lineinfo.m_value;
                break;
                case TYPE:
                    type = true;
                    dc.m_type = lineinfo.m_value;
                break;
                case ROOM:
                    room = true;
                    dc.m_room = lineinfo.m_value;
                break;
                case FLOOR:
                    floor = true;
                    dc.m_floor = atoi( lineinfo.m_value.c_str() );
                break;
                case LOG:
                    log = true;
                    dc.m_log = lineinfo.m_value;
                break;
                case CONFIGLINE:
                    config = true;
                    dc.m_configline = lineinfo.m_value;
                break;

                
            }
            // all fields are set
            if (id&&type&&room&&floor&&log&&config)
            {
                break;
            }
        }
        if (id&&type&&room&&floor&&log&&config)
        {
//            cout << "Pushing " << dc.m_id << " " << dc.m_type << " " << dc.m_room << " " << dc.m_floor << " " << dc.m_configline << " " << endl ;
            _vec.push_back(dc);
        }
    }
    return;
}