// Brittle C++ Library - Enums - Orientation Header

#ifndef __BRITTLE_ENUMS_ORIENTATION_H
#define __BRITTLE_ENUMS_ORIENTATION_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>


namespace Brittle
{

///////////////////////////////////////////////////////////////////////////////
//
// Orientation
//

enum OrientationValue
{
    ORIENTATION_NONE          = 0,

    ORIENTATION_VERTICAL      = 0x01,
    ORIENTATION_HORIZONTAL    = 0x02,
};


///////////////////////////////////////////////////////////////////////////////
//
// Orientation
//

class Orientation
{
public:
    Orientation() {}
    Orientation( OrientationValue value ) : m_value( value ) {}

    operator OrientationValue() const { return m_value; }

private:
    OrientationValue m_value { ORIENTATION_NONE };
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle

#endif // __BRITTLE_ENUMS_ORIENTATION_H
