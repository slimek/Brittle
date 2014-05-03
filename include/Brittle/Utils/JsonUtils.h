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

Bool QueryInt   ( const Json::Value& json, const std::string& name, Int& value );
Bool QueryFloat ( const Json::Value& json, const std::string& name, Float& value );
Bool QueryString( const Json::Value& json, const std::string& name, std::string& value );
Bool QueryArray ( const Json::Value& json, const std::string& name, Json::Value& value );


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle

#endif // __BRITTLE_UTILS_JSON_UTILS_H
