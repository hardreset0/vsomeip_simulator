

#ifndef  _IAPP_
#define  _IAPP_

class IApp
{
    public:
    virtual void init() = 0;
    virtual void run()  = 0;

    virtual void offer_service() = 0;

    virtual void offer_event()  = 0;

    virtual void stop_offer_service() = 0;

    virtual void stop_offer_event()   = 0; 

    private:
    virtual void register_all_methods() = 0;
    virtual void register_all_events()  = 0;

};


#endif