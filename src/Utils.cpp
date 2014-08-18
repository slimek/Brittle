// Brittle C++ Library - Utilities Implementation

#include "BrittlePch.h"

#include <Brittle/Utils/Geometry.h>


namespace Brittle
{

//
// Content
//
//   Caramel::ToString
//

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
