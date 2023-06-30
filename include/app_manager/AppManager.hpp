

#ifndef _APP_MANAGER_
#define _APP_MANAGER_


#include "IAppManager.hpp"
#include "ThreadCommands.hpp"
#include "someip_datatypes.hpp"
#include <vector>
#include <map>
#include <iostream>
#include "App.hpp"

using threadPool = utilities::ThreadCommands<std::function<void(void)>, 50>;

class AppManager : public IAppManager
{
    public:

    AppManager() = default;

    void createApplication(someip::application app) override
    {
        //1. create thread.
        auto thread_id = this->m_threads.run([app](){
            App new_app{app};
            new_app.init();
            new_app.run();
        });

        std::cout << app.m_app_name << "  " << thread_id << std::endl;
      
        this->apps.insert({app.m_app_name, thread_id});
    }

    void waitingAllApplications() override
    {
        this->m_threads.waitingAllThreads();
    }

    private:
    std::map<someip::application_name, threadPool::thread_id> apps;
    threadPool m_threads;

};




#endif