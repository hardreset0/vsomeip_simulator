



#ifndef _I_CONFIGURATION_READER_
#define _I_CONFIGURATION_READER_

#include <string>

class IConfigurationReader
{
    public:
    virtual bool loadConfiguration(const std::string & configuration) = 0;
};



#endif