

#ifndef _SOMEIP_TYPES_
#define _SOMEIP_TYPES_
#include <string>
#include <map>
#include <vector>

namespace someip
{
    typedef std::string                         paramater_name;
    typedef std::string                         paramater_type;
    typedef std::string                         instance_id;
    typedef std::string                         service_id;
    typedef std::string                         method_id;
    typedef std::string                         event_id;
    typedef std::string                         application_name;
    typedef std::string                         is_under_test;
    typedef std::vector<std::string>            applications_name;

    typedef  std::map<paramater_name, paramater_type> inputs;
    typedef  std::map<paramater_name, paramater_type> outputs;

    
    typedef std::string                         is_service;

    struct method 
    {
        std::string m_name;
        method_id   m_method_id;
        inputs      m_inputs;
        outputs     m_outputs;
    };

    struct event
    {
        // TODO: to be defined. 
        std::string     m_name;
        event_id        m_event_id; 
        inputs          m_inputs;
        outputs         m_outputs;
    };

    typedef std::vector<method>                 methods;
    typedef std::vector<event>                  events;
    
    struct application
    {
        application_name                m_app_name;
        service_id                      m_service_id;
        is_service                      m_is_service;
        is_under_test                   m_is_under_test;
        instance_id                     m_instance_id;
        methods                         m_methods;
        events                          m_events;
    };
    typedef std::vector<application>       applications;

}
#endif