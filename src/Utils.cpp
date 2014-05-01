// Brittle C++ Library - Utilities Implementation

#include "BrittlePch.h"

#include <Brittle/Utils/JsonUtils.h>


namespace Brittle
{

//
// Content
//
//   JsonUtils
//

///////////////////////////////////////////////////////////////////////////////
//
// JSON Utilities
//

Bool QueryFloat( const Json::Value& json, const std::string& name, Float& value )
{
    if ( ! json.isMember( name )) { return false; }

    const auto& ref = json[ name ];

    if ( ! ref.isConvertibleTo( Json::realValue )) { return false; }

    value = static_cast< Float >( ref.asDouble() );
    return true;
}


Bool QueryString( const Json::Value& json, const std::string& name, std::string& value )
{
    if ( ! json.isMember( name )) { return false; }

    const auto& ref = json[ name ];

    if ( ! ref.isConvertibleTo( Json::stringValue )) { return false; }

    value = ref.asString();
    return true;
}


Bool QueryArray( const Json::Value& json, const std::string& name, Json::Value& value )
{
    if ( ! json.isMember( name )) { return false; }

    const auto& ref = json[ name ];
    
    if ( ! ref.isConvertibleTo( Json::arrayValue )) { return false; }

    value = ref;
    return true;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle
