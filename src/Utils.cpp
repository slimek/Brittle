// Brittle C++ Library - Utilities Implementation

#include "BrittlePch.h"

#include <Brittle/Utils/Geometry.h>
#include <Brittle/Utils/Styling.h>
#include <Caramel/Numeric/UnionBits.h>


namespace Brittle
{

//
// Content
//
//   MakeColor
//   Caramel::ToString
//

///////////////////////////////////////////////////////////////////////////////
//
// Color Helpers
//

Color3B MakeColor3B( Uint32 hexColor )
{
    // Format: RGB, lower 24-bit

    UnionBits32 b32;
    b32.ui = hexColor;
    return Color3B( b32.qb.mh, b32.qb.ml, b32.qb.lo );
}


Color4B MakeColor4B( Uint32 hexColor )
{
    // Format: RGBA

    UnionBits32 b32;
    b32.ui = hexColor;
    return Color4B( b32.qb.hi, b32.qb.mh, b32.qb.ml, b32.qb.lo );
}


} // namespace Brittle

namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// To String Functions
//

std::string ToString( const cocos2d::Vec2& vec )
{
    return Format( "({0}, {1})", vec.x, vec.y );
}


std::string ToString( const cocos2d::Size& size )
{
    return Format( "({0}, {1})", size.width, size.height );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel
