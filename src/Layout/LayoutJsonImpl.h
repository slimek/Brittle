// Brittle C++ Library - Layout - Layout JSON Private Header

#ifndef __BRITTLE_LAYOUT_LAYOUT_JSON_IMPL_H
#define __BRITTLE_LAYOUT_LAYOUT_JSON_IMPL_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>
#include <Brittle/Layout/LayoutJson.h>
#include <Brittle/Utils/JsonValue.h>


namespace Brittle
{

///////////////////////////////////////////////////////////////////////////////
//
// Layout JSON
//

class LayoutJsonImpl
{
public:

    LayoutJsonImpl( const std::string& name, const JsonValue& json );

    std::string GetName() const { return m_name; }

    Bool GetItem( const std::string& itemName, JsonValue& item ) const;


private:

    std::string m_name;
    JsonValue   m_json;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle

#endif // __BRITTLE_LAYOUT_LAYOUT_JSON_IMPL_H
