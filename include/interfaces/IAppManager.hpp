


#ifndef  _IAPP_MANAGER_
#define  _IAPP_MANAGER_

#include <string>
#include "someip_datatypes.hpp"

class IAppManager 
{
    public:
    
    virtual void createApplication(someip::application) = 0;
    virtual void waitingAllApplications() = 0;

};



#endif