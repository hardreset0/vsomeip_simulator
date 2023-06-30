


#ifndef _JSON_CONFIGURATION_READER
#define _JSON_CONFIGURATION_READER

#include "IConfigurationReader.hpp"
#include "rapidjson/document.h"
#include "rapidjson/encodings.h"

namespace utilities
{
    typedef rapidjson::GenericValue<rapidjson::UTF8<>>::ConstMemberIterator             resultIterator;
    typedef rapidjson::GenericValue<rapidjson::UTF8<>>::ConstArray                      Entries;
    typedef rapidjson::GenericValue<rapidjson::UTF8<>>                                  singleEntry;
    typedef rapidjson::GenericValue<rapidjson::UTF8<>>::ConstObject                     Object;
    class Json : public IConfigurationReader
    {
        public:

        Json() = default;
        bool loadConfiguration(const std::string & configuration) override;
        
        Entries getEntries( const std::string & key ) const;
        Entries getEntries( const singleEntry & entry , const std::string & key ) const;
        bool getEntry(  const singleEntry & entry  , const std::string & key_name , std::string & key_value  ) const;
        

        Object getObject(const singleEntry & entry, const std::string & key_name);
        
        resultIterator invaliedIterator() const;
        ~Json() = default;

        private:
        rapidjson::Document m_doc;
    };
}


#endif