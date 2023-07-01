



#ifndef _APPS_SIMULATOR_
#define _APPS_SIMULATOR_

#include "ConfigurationAdapter.hpp"
#include "IApp.hpp"
#include <vsomeip/vsomeip.hpp>

class App : public IApp
{
    public:
    App(someip::application app);

    void init() override;
    void run() override;
    
    void offer_service() override;

    void offer_event() override;

    void stop_offer_service() override;

    void stop_offer_event() override; 

  
    private:
    void register_all_methods() override;

    void register_all_events() override;

    void on_message(const std::shared_ptr<vsomeip::message> &_request);

    someip::application application_data;
    std::shared_ptr< vsomeip::application > app;

};



#endif