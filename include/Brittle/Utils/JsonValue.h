// Brittle C++ Library - Utils - JSON Value Header

#ifndef __BRITTLE_UTILS_JSON_VALUE_H
#define __BRITTLE_UTILS_JSON_VALUE_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>
#include <JsonCpp/value.h>
#include <boost/optional.hpp>

// the GetObject macro in <wingdi.h> is evil ~
#if defined( CARAMEL_SYSTEM_IS_WINDOWS ) && defined( GetObject )
#undef GetObject
#endif


namespace Brittle
{

///////////////////////////////////////////////////////////////////////////////
//
// JSON Value
// - A lightweight wrapper of JsonCpp Value.
//   Make the get-value process simpler.
//

class JsonValue
{
public:

    JsonValue() {}

    // Tag is for tracing and error messages.
    JsonValue( const Json::Value& json, const std::string& tag );

    void SetTag( const std::string& tag );


    //
    // Basic Accessors
    //

    Json::Value GetJson() const { return m_json; }


    //
    // Get Values of Object
    // - Use these functions the get an object's sub-values.
    //   If the value doesn't exist, returns false.
    //   If the value is not convertible to the required type,
    //   alerts then returns false.
    //

    Bool GetBool  ( const std::string& name, Bool& value ) const;
    Bool GetInt   ( const std::string& name, Int& value ) const;
    Bool GetFloat ( const std::string& name, Float& value ) const;
    Bool GetString( const std::string& name, std::string& value ) const;
    Bool GetArray ( const std::string& name, JsonValue& value ) const;
    Bool GetObject( const std::string& name, JsonValue& value ) const;
    Bool GetValue ( const std::string& name, JsonValue& value ) const;

    Bool GetArray ( const std::string& name, Json::Value& value ) const;
    Bool GetObject( const std::string& name, Json::Value& value ) const;
    Bool GetValue ( const std::string& name, Json::Value& value ) const;


    //
    // Get Value, copy onto an optional
    //

    Bool GetString( const std::string& name, boost::optional< std::string >& value ) const;


    //
    // Predicates
    //

    Bool ContainsKey( const std::string& name ) const;


private:
    
    Json::Value m_json;
    std::string m_tag;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle

#endif // __BRITTLE_UTILS_JSON_VALUE_H
