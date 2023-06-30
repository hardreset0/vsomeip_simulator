



#ifndef _APPS_SIMULATOR_
#define _APPS_SIMULATOR_

#include "ConfigurationAdapter.hpp"
#include "IApp.hpp"

class App // TODO: public IApp
{
    public:
    App(someip::application app);

    void init();
    void run();

    private:
    someip::application application_data;

};



#endif