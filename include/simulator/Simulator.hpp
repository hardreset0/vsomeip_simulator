

#ifndef _SIMULATOR_
#define _SIMULATOR_

#include <memory>

class Simulator_impl;

class Simulator 
{
    public:
        Simulator();

        void init();
        void run();
        ~Simulator();

    private:
    std::unique_ptr<Simulator_impl> m_impl;
};


#endif