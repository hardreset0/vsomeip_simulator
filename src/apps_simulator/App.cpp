


#include "App.hpp"
#include "someip_datatypes.hpp"
#include <iostream>
#include <thread>
#include <chrono>

App::App(someip::application app):application_data(app)
{
    std::cout << "Application [  " << app.m_app_name << " ] is started. " << std::endl;
}

void App::init()
{
    // //TODO: create vsomeip application.
    // std::cout << "create vsomeip application .. " << std::endl;
    // //TODO: init app.
    // std::cout << "init vsomeip application .. " << std::endl;
    // //TODO: register all methods and events.
    // std::cout << "register vsomeip methods and events .. " << std::endl;
    // //TODO: offer service.
    // std::cout << "offer service .. " << std::endl;
}

void App::run()
{
    // TODO: start.
    std::cout << "start .. " << std::endl;
    while(true)
    {
        std::cout << "still Alive"  << application_data.m_app_name << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(15));
    }
}


