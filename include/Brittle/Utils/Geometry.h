// Brittle C++ Library - Utils - Geometry Header

#ifndef __BRITTLE_UTILS_GEOMETRY_H
#define __BRITTLE_UTILS_GEOMETRY_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>


namespace Brittle
{

///////////////////////////////////////////////////////////////////////////////
//
// Rect Helpers
//

inline Rect MakeRect( const Vector2& origin, const Size& size )
{
    Rect r;
    r.origin = origin;
    r.size = size;
    return r;
}


inline Rect MakeRect( const Size& size )
{
    Rect r;  // origin's default is ( 0, 0 )
    r.size = size;  
    return r;
}


inline Vector2 GetCenter( const Rect& rect )
{
    return Vector2( rect.getMidX(), rect.getMidY() );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle

#endif // __BRITTLE_UTILS_GEOMETRY_H
