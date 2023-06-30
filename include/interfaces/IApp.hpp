

#ifndef  _IAPP_
#define  _IAPP_

class IApp
{
    public:
    virtual void init() = 0;
    virtual void run()  = 0;
    // TODO: 
    virtual void offer_service();
    //TODO: 
    virtual void offer_event();

    //TODO: 
    virtual void stop_offer_service();

    //TODO:
    virtual void stop_offer_event();

    //TODO:

    private:
    virtual void on_messageHandler() = 0;

};


#endif