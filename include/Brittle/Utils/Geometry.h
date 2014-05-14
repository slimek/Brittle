// Brittle C++ Library - Utils - Geometry Header

#ifndef __BRITTLE_UTILS_GEOMETRY_H
#define __BRITTLE_UTILS_GEOMETRY_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>
#include <math/CCGeometry.h>


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


} // namespace Brittle


///////////////////////////////////////////////////////////////////////////////
//
// ToString Helper Functions
//

namespace Caramel
{

std::string ToString( const cocos2d::Size& size );


} // namespace Caramel

///////////////////////////////////////////////////////////////////////////////

#endif // __BRITTLE_UTILS_GEOMETRY_H
