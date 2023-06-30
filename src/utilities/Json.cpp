



#include "Json.hpp"
#include "rapidjson/document.h"
#include "rapidjson/rapidjson.h"
#include <cstddef>
#include <iostream>
#include <cstdio>
#include <stdexcept>

namespace utilities
{
    bool Json::loadConfiguration(const std::string & configuration)
    {
        this->m_doc.Parse(configuration.c_str());
        return m_doc.HasParseError() == false;
    }

    Entries Json::getEntries( const std::string & key ) const
    {
        if (false == this->m_doc[key.c_str()].IsArray())
        {
            // TODO: through new exception.
        }

        return this->m_doc[key.c_str()].GetArray();
    }

    bool Json::getEntry(  const singleEntry & entry  , const std::string & key_name , std::string & key_value  ) const
    {
        auto iterator = entry.FindMember(key_name.c_str());

        if (iterator != this->invaliedIterator())
        {   
            key_value = iterator->value.GetString();    
            return true;
        }

        return false;
    }
    Entries Json::getEntries( const singleEntry & entry , const std::string & key_name ) const
    {
        auto iterator = entry.FindMember(key_name.c_str());

        if (iterator == this->invaliedIterator() || iterator->value.IsArray() == false)
        {
            throw std::runtime_error( "Key: [" + key_name + "] does not exists.");
        }

        return iterator->value.GetArray();
    }
    Object Json::getObject(const singleEntry & entry, const std::string & key_name)
    {
        auto iterator = entry.FindMember(key_name.c_str());

        if (iterator != this->invaliedIterator())
        {
            return  entry[key_name.c_str()].GetObject();
        }

        // TODO: throw new exception.
    }

    resultIterator Json::invaliedIterator() const
    {
        return this->m_doc.MemberEnd();
    }
}
