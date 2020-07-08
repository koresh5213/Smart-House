#ifndef CONFIG_LINE_PARSER_H
#define CONFIG_LINE_PARSER_H

#include "DeviceAgent.h"

#include <string>
#include <vector>
#include <stdexcept>

class DeviceAgent;

class ConfigFileParser
{

enum LineType{ID, TYPE, ROOM, FLOOR, LOG, CONFIGLINE, EMPTY, ERROR};

struct LineInfo
{
    LineType        m_type;
    std::string     m_value;
};

public:
    ConfigFileParser(const std::string& _path = ".");
public:
    void Parse (std::vector<DeviceConfig>&) throw(std::runtime_error);
public: //TODO: change to private
    struct LineInfo ParseLine(const std::string&);
private:
    bool HasOnlySpaces(const std::string& str);
private:
    std::string m_path;
};

#endif