


#ifndef THREAD_COMMANDS
#define THREAD_COMMANDS


#include "IThreadCommands.hpp"
#include <cstddef>
#include <thread>
#include <array>
#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>

namespace utilities
{
    using namespace interfaces;
    template<class Task, size_t Number_of_Threads>
    class ThreadCommands : public IThreadCommands<Task>
    {
        public:

        typename ThreadCommands<Task, Number_of_Threads>::thread_id run(Task thread_function)
        {
            if (this->m_threads_counter > 0)
            {
                std::thread new_thread(std::move(thread_function));

                this->m_threadPool.push_back(std::move( new_thread ));
                this->m_threads_counter--;
                //TODO: return thread ID.
                return Number_of_Threads - m_threads_counter;
            }
            //TODO: throw new exception.
            return 0;
        }

        void stop(typename ThreadCommands<Task, Number_of_Threads>::thread_id thread_id)
        {
            std::cout << "stopping !" << std::endl;
        }

        void waitingAllThreads ()
        {
            std::for_each( this->m_threadPool.begin(), this->m_threadPool.end(), [this](auto& unit_of_execution){
                unit_of_execution.join();
            });
    
            std::cout << "Waiting .." << std::endl;
        }

        private:
        std::vector<std::thread> m_threadPool; 
        size_t m_threads_counter = Number_of_Threads;
    };
};





#endif