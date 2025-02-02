


#include "App.hpp"
#include "someip_datatypes.hpp"
#include <cstddef>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <algorithm>

App::App(someip::application app):application_data(app)
{
    std::cout << "Application [  " << app.m_app_name << " ] init process. " << std::endl;
}

void App::init()
{
    //this->application_data.
    // //TODO: create vsomeip application.
    // std::cout << "create vsomeip application .. " << std::endl;
    // //TODO: init app.
    // std::cout << "init vsomeip application .. " << std::endl;
    // //TODO: register all methods and events.
    // std::cout << "register vsomeip methods and events .. " << std::endl;
    // //TODO: offer service.
    // std::cout << "offer service .. " << std::endl;

    this->app = vsomeip::runtime::get()->create_application(this->application_data.m_app_name);
    this->app->init();
    this->register_all_methods();
    this->app->offer_service(std::stoul(this->application_data.m_service_id, nullptr, 16), std::stoul(this->application_data.m_instance_id, nullptr, 16),
    1);

}

void App::run()
{
    app->start();
}


void App::offer_service()
{

}

void App::offer_event()
{

}

void App::stop_offer_service()
{

}

void App::stop_offer_event()
{

}

  
void App::register_all_methods()
{
    std::for_each(this->application_data.m_methods.begin(), this->application_data.m_methods.end(), [this](const someip::method method){
        auto auto_service_id = std::stoul(this->application_data.m_service_id, nullptr, 16);
        auto auto_instance_id = std::stoul(this->application_data.m_instance_id, nullptr, 16);
        auto auto_method_id   = std::stoul(method.m_method_id, nullptr, 16);

        

        this->app->register_message_handler(
        auto_service_id, 
        auto_instance_id,
        auto_method_id, 
        [this](const std::shared_ptr<vsomeip::message> &_request){ 
            this->on_message(_request);
        });
    });
    
}

//TODO: need some customization.
void App::on_message(const std::shared_ptr<vsomeip::message> &_request)
{
    std::shared_ptr<vsomeip::payload> its_payload = _request->get_payload();
    vsomeip::length_t l = its_payload->get_length();

    // Get payload
    std::stringstream ss;
    for (vsomeip::length_t i=0; i<l; i++) {
       ss << std::setw(2) << std::setfill('0') << std::hex
          << (int)*(its_payload->get_data()+i) << " ";
    }

    std::cout << "SERVICE: Received message with Client/Session ["
        << std::setw(4) << std::setfill('0') << std::hex << _request->get_client() << "/"
        << std::setw(4) << std::setfill('0') << std::hex << _request->get_session() << "] "
        << ss.str() << std::endl;

    // Create response
    
    std::shared_ptr<vsomeip::message> its_response = vsomeip::runtime::get()->create_response(_request);
    its_payload = vsomeip::runtime::get()->create_payload();

    
    std::vector<vsomeip::byte_t> its_payload_data;
    its_payload_data.push_back(0x00);
    its_payload_data.push_back(0x00);
    its_payload_data.push_back(0x00);
    its_payload_data.push_back(0x0A);
    its_payload_data.push_back(0xEF);
    its_payload_data.push_back(0xBB);
    its_payload_data.push_back(0xBF);
    for (int i=70; i>=65; i--) {
        its_payload_data.push_back(i % 256);
    }
    its_payload_data.push_back('\0');
    its_payload->set_data(its_payload_data);
    its_response->set_payload(its_payload);
    app->send(its_response);

}

void App::register_all_events() 
{

}


