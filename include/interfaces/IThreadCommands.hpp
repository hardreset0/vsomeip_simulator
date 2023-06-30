

#ifndef _ITHREAD_COMMANDS_
#define _ITHREAD_COMMANDS_

#include <functional>


namespace interfaces
{
    template<class Task>
    class IThreadCommands
    {
        public: 
        typedef uint32_t thread_id;

        public:
        
        thread_id run(Task);

        virtual void stop(thread_id) = 0;

        virtual void waitingAllThreads () = 0;
    };
};




#endif