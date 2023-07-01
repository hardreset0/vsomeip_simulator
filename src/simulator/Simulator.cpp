



#include "someip_datatypes.hpp"
#include <chrono>
#include <iostream>
#include <functional>
#include "AppManager.hpp"
#include "ConfigurationAdapter.hpp"
#include <memory>
#include <thread>
#include "Simulator.hpp"
#include <chrono>


const std::string path {"./env.json"};

class Simulator_impl
{
    public:
    Simulator_impl() = default;
    void init();
    void run();
    ~Simulator_impl() = default;

    private: 
    someip::ConfigurationAdapter m_configuration{path};
    AppManager m_app_manager{};
};




void Simulator_impl::init()
{
    //TODO: init event executor.
        //TODO: related to UI.
    // TODO: get all application.
    auto apps_name = this->m_configuration.getApplicationsByName();

    //this->m_app_manager.createApplication();

    std::for_each(apps_name.begin(), apps_name.end(), [this](someip::application_name app_name){
        // get app.
        auto app = this->m_configuration.getApplication(app_name);
        this->m_app_manager.createApplication(app);
    });
    // for each application ..
        // create App env for it.
        // init.
        // run.
    std::this_thread::sleep_for(std::chrono::seconds(20));
    //this->m_sim.init();
}

void Simulator_impl::run()
{
    // TODO: ask user for a testcase path.
    // TODO: decode testcase to apps and commands.
    // TODO: waiting all threads ?
    this->m_app_manager.waitingAllApplications();

}



Simulator::Simulator(): m_impl(std::make_unique<Simulator_impl>())
{
    std::cout << "VSOMEIP simulator is started ... " << std::endl;
}

Simulator::~Simulator() = default;


void Simulator::init()
{
    this->m_impl->init();
}

void Simulator::run()
{
    std::cout << "simulator run  .... " << std::endl;
    // before running wait some time for all threads to be init.
    this->m_impl->run();
}