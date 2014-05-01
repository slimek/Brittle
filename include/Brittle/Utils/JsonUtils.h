// Brittle C++ Library - Utils - JSON Utilities Header

#ifndef __BRITTLE_UTILS_JSON_UTILS_H
#define __BRITTLE_UTILS_JSON_UTILS_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>
#include <JsonCpp/value.h>


namespace Brittle
{

///////////////////////////////////////////////////////////////////////////////
//
// JsonCpp Utility Functions
//

//
// Query Functions
// - Return false if 
//   1. The value doesn't exist.
//   2. The value is not convertible to the required type.
//

inline Bool QueryArray( const Json::Value& json, const std::string& name, Json::Value& value )
{
    if ( ! json.isMember( name )) { return false; }

    const auto& temp = json[ name ];
    
    if ( ! temp.isConvertibleTo( Json::arrayValue )) { return false; }

    value = temp;
    return true;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle

#endif // __BRITTLE_UTILS_JSON_UTILS_H
