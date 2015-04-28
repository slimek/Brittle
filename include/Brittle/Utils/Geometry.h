// Brittle C++ Library - Utils - Geometry Header

#ifndef __BRITTLE_UTILS_GEOMETRY_H
#define __BRITTLE_UTILS_GEOMETRY_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>
#include <math/CCGeometry.h>
#include <algorithm>


namespace Brittle
{

///////////////////////////////////////////////////////////////////////////////
//
// Geometry Types Comparison Operators
// - NOTES: Vec2 supports comparison by itself.
//

inline Bool operator==( const Size& lhs, const Size& rhs )
{
    return lhs.width == rhs.width && lhs.height == rhs.height;
}


inline Bool operator!=( const Size& lhs, const Size& rhs )
{
    return ! operator==( lhs, rhs );
}


inline Bool operator==( const Rect& lhs, const Rect& rhs )
{
    return lhs.origin == rhs.origin && lhs.size == rhs.size;
}


inline Bool operator!=( const Rect& lhs, const Rect& rhs )
{
    return ! operator==( lhs, rhs );
}


///////////////////////////////////////////////////////////////////////////////
//
// Rect Helpers
//

inline Rect MakeRect( const Vec2& origin, const Size& size )
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


inline Vec2 GetCenter( const Rect& rect )
{
    return Vec2( rect.getMidX(), rect.getMidY() );
}


///////////////////////////////////////////////////////////////////////////////
//
// Size Helpers
//

inline Vec2 GetCenter( const Size& size )
{
    return size / 2.0;
}


///////////////////////////////////////////////////////////////////////////////
//
// Circle Radius Helper
// - For building circle physics bodies.
//

// Get the radius of circle which can be put into the box.
inline Float InnerRadius( const Rect& box )
{
    return std::min( box.size.width, box.size.height ) / 2.0f;
}


} // namespace Brittle


///////////////////////////////////////////////////////////////////////////////
//
// ToString Helper Functions
//

namespace cocos2d
{

std::string ToString( const cocos2d::Vec2& vec );
std::string ToString( const cocos2d::Size& size );


} // namespace cocos2d

///////////////////////////////////////////////////////////////////////////////

#endif // __BRITTLE_UTILS_GEOMETRY_H
