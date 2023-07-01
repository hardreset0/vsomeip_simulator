

#include "ConfigurationAdapter.hpp"
#include "IFileHandler.hpp"
#include <exception>
#include <memory>
#include <iostream>
#include <functional>
#include <stdexcept>
#include  <utility>

namespace someip
{
    ConfigurationAdapter::ConfigurationAdapter(const std::string & path):
    m_file{std::make_unique<FileHandler>()}
    {
        if ( false == this->init(path) )
        {
            // issue: throw exception. 
            std::cout << "can not open file ... " << std::endl;
        }
    }

    bool ConfigurationAdapter::init(const std::string & path)
    {
        auto file = this->m_file->openFile(path);

        if (false == file) return false; 


        bool ok = this->m_jsonHandler.loadConfiguration( this->m_file.getData() );

        if (!ok) return false;

        auto entires = this->m_jsonHandler.getEntries("Applications");
        for(auto const & data : entires)
        {
            // create struct. 
            struct application _app;
            struct method      _method;
            struct event       _event;


            this->m_jsonHandler.getEntry(data, "name" , _app.m_app_name);
            this->m_jsonHandler.getEntry(data, "is_service" , _app.m_is_service);
            this->m_jsonHandler.getEntry(data, "service_id" , _app.m_service_id);
            this->m_jsonHandler.getEntry(data, "under_test" , _app.m_is_under_test);


            try 
            {
                auto methods_entries = this->m_jsonHandler.getEntries( data , "methods");
                // note: populate method.
                for (auto const& entry : methods_entries)
                {
                    // m_name
                    this->m_jsonHandler.getEntry(entry, "name", _method.m_name);
                    this->m_jsonHandler.getEntry(entry, "method_id", _method.m_method_id);

                    // method parameters.
                    auto paramaters = this->m_jsonHandler.getObject(entry, "in");

                    for (const auto & par : paramaters)
                    {
                        _method.m_inputs.insert(std::make_pair(par.name.GetString(), par.value.GetString()));
                    }     
                    

                    // method output.
                    auto outputs = this->m_jsonHandler.getObject(entry, "out");

                    for (const auto & output: outputs)
                    {
                        _method.m_outputs.insert(std::make_pair( output.name.GetString(), output.value.GetString() ));
                    }
                    _app.m_methods.push_back(_method);  
                }

            }
            catch(std::runtime_error exception)
            {
                std::cout << exception.what() << std::endl;
            }

            try 
            {
                // events entries.
                auto events_entries = this->m_jsonHandler.getEntries( data , "events");
                for (auto const& entry : events_entries)
                {
                    // m_name
                    this->m_jsonHandler.getEntry(entry, "name", _event.m_name);
                    this->m_jsonHandler.getEntry(entry, "event_id", _event.m_event_id);

                    // method parameters.
                    auto paramaters = this->m_jsonHandler.getObject(entry, "in");

                    for (const auto & par : paramaters)
                    {
                        _event.m_inputs.insert(std::make_pair(par.name.GetString(), par.value.GetString()));
                    }     
                    

                    // method output.
                    auto outputs = this->m_jsonHandler.getObject(entry, "out");

                    for (const auto & output: outputs)
                    {
                        _event.m_outputs.insert(std::make_pair( output.name.GetString(), output.value.GetString() ));
                    }
                    _app.m_events.push_back(_event);  
                }

            }
            catch(std::runtime_error exception)
            {
                std::cout << exception.what() << " " << std::endl;
            }

            //TODO: event.
            this->m_someip_applications.push_back(_app);
        }
        return true;
    }

    const applications_name ConfigurationAdapter::getApplicationsByName()  const
    {
        applications_name applicationsName;
        
        std::for_each( this->m_someip_applications.begin(), this->m_someip_applications.end(), [&applicationsName](application app){
            applicationsName.push_back(app.m_app_name);
        } );

        return applicationsName;
    }

    const bool ConfigurationAdapter::is_service(const application_name & app_name) const
    {
        bool is_service = false;
        std::for_each( this->m_someip_applications.begin(), this->m_someip_applications.end(), [app_name,&is_service](application app){
            if ( app.m_app_name == app_name &&  app.m_is_service == std::string("true") ) is_service = true;
        } );
        return is_service; 
    }

    const service_id ConfigurationAdapter::getServiceID(const application_name & app_name)  const
    {
        service_id service_id_value = "0x00";
        std::for_each( this->m_someip_applications.begin(), this->m_someip_applications.end(), [app_name,&service_id_value](application app){
            if ( app.m_app_name == app_name  ) service_id_value = app.m_service_id;
        } );

        return service_id_value;
    }

    const instance_id ConfigurationAdapter::getInstanceID(const application_name & app_name) const
    {
        instance_id instance_id_value = "0x00";
        std::for_each( this->m_someip_applications.begin(), this->m_someip_applications.end(), [app_name,&instance_id_value](application app){
            if ( app.m_app_name == app_name  ) instance_id_value = app.m_instance_id;
        } );

        return instance_id_value;
    }

    const bool ConfigurationAdapter::is_underTest(const application_name & app_name)  const
    {
        bool under_test = false;
        std::for_each( this->m_someip_applications.begin(), this->m_someip_applications.end(), [app_name,&under_test](application app){
            if ( app.m_app_name == app_name  && app.m_is_under_test == "true") under_test = true;
        } );

        return under_test;
    }

    const methods ConfigurationAdapter::getAllMethods( const application_name & app_name ) const
    {
        methods _methods;

        std::for_each( this->m_someip_applications.begin(), this->m_someip_applications.end(), [app_name,&_methods](application app){
            if (app.m_app_name == app_name) 
            {
                _methods = app.m_methods;
                return;
            }
        } );
        return _methods;
    }

    const events  ConfigurationAdapter::getAllEvents(const application_name & app_name) const
    {
        events _event;

        std::for_each( this->m_someip_applications.begin(), this->m_someip_applications.end(), [app_name,&_event](application app){
            if (app.m_app_name == app_name) 
            {
                _event = app.m_events;
                return;
            }
        } );
        return _event;
    }

    const application ConfigurationAdapter::getApplication(const application_name & app_name) const
    {
        application _app;
        std::for_each( this->m_someip_applications.begin(), this->m_someip_applications.end(), [app_name,&_app](application app){
            if (app.m_app_name == app_name) 
            {
                _app = app;
                return;
            }
        } );
        return _app;
    }
}

