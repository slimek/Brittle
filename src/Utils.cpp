// Brittle C++ Library - Utilities Implementation

#include "BrittlePch.h"

#include <Brittle/Utils/JsonValue.h>


namespace Brittle
{

//
// Content
//
//   JsonValue
//

///////////////////////////////////////////////////////////////////////////////
//
// JSON Value
//

JsonValue::JsonValue( const Json::Value& json, const std::string& tag )
    : m_json( json )
    , m_tag( tag )
{
}


void JsonValue::SetTag( const std::string& tag )
{
    m_tag = tag;
}


//
// Get Value
//

Bool JsonValue::GetInt( const std::string& name, Int& value ) const
{
    if ( ! m_json.isMember( name )) { return false; }

    const auto& ref = m_json[ name ];

    if ( ! ref.isConvertibleTo( Json::intValue ))
    {
        CARAMEL_ALERT( "%s : \"%s\" is not convertible to int", m_tag, name );
        return false;
    }

    value = ref.asInt();
    return true;
}


Bool JsonValue::GetFloat( const std::string& name, Float& value ) const
{
    if ( ! m_json.isMember( name )) { return false; }

    const auto& ref = m_json[ name ];

    if ( ! ref.isConvertibleTo( Json::realValue ))
    {
        CARAMEL_ALERT( "%s : \"%s\" is not convertible to float", m_tag, name );
        return false;
    }

    value = static_cast< Float >( ref.asDouble() );
    return true;
}


Bool JsonValue::GetString( const std::string& name, std::string& value ) const
{
    if ( ! m_json.isMember( name )) { return false; }

    const auto& ref = m_json[ name ];

    if ( ! ref.isConvertibleTo( Json::stringValue ))
    {
        CARAMEL_ALERT( "%s : \"%s\" is not convertible to string", m_tag, name );
        return false;
    }

    value = ref.asString();
    return true;
}


Bool JsonValue::GetArray( const std::string& name, Json::Value& value ) const
{
    if ( ! m_json.isMember( name )) { return false; }

    const auto& ref = m_json[ name ];
    
    if ( ! ref.isConvertibleTo( Json::arrayValue ))
    {
        CARAMEL_ALERT( "%s : \"%s\" is not convertible to array", m_tag, name );
        return false;
    }

    value = ref;
    return true;
}


Bool JsonValue::GetObject( const std::string& name, Json::Value& value ) const
{
    if ( ! m_json.isMember( name )) { return false; }

    const auto& ref = m_json[ name ];
    
    if ( ! ref.isConvertibleTo( Json::objectValue ))
    {
        CARAMEL_ALERT( "%s : \"%s\" is not convertible to object", m_tag, name );
        return false;
    }

    value = ref;
    return true;
}


//
// Get Value, Copy onto Optional
//

Bool JsonValue::GetString( const std::string& name, boost::optional< std::string >& value ) const
{
    std::string s;
    if ( this->GetString( name, s ))
    {
        value = s;
        return true;
    }
    return false;
}


//
// Predicates
//

Bool JsonValue::ContainsKey( const std::string& name ) const
{
    return m_json.isMember( name );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle
