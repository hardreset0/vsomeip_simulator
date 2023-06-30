



#ifndef _CONFIGURATION_ADAPETER_
#define _CONFIGURATION_ADAPETER_

#include "Json.hpp"
#include "IFileHandler.hpp"
#include "FileHandler.hpp"
#include "someip_datatypes.hpp"

namespace someip
{
    class ConfigurationAdapter
    {
        public:
        ConfigurationAdapter(const std::string & path);

        const applications_name getApplicationsByName()              const; 

        const bool is_service(const application_name & name)           const;

        const service_id getServiceID(const application_name & name)   const;

        const instance_id getInstanceID(const application_name & name) const;

        const bool is_underTest(const application_name & name)         const;

        const methods getAllMethods( const application_name & name )   const;

        const events  getAllEvents(const application_name & name)      const;

        const application getApplication(const application_name & name) const;

        private:
        std::unique_ptr<IFileHandler> m_file;
        rapidjson::Document doc;
        utilities::Json m_jsonHandler;
        applications m_someip_applications;

        bool init(const std::string & path);

    };
}




#endif




