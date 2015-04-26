// Brittle C++ Library - Utils - Styling Header

#ifndef __BRITTLE_UTILS_STYLING_H
#define __BRITTLE_UTILS_STYLING_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>
#include <base/ccTypes.h>


namespace Brittle
{

///////////////////////////////////////////////////////////////////////////////
//
// Color Helpers
//

// 24-bit hexidecimal color in RGB format.
// - e.g. red is 0xFF0000, blue is 0x0000FF.
Color3B MakeColor3B( Uint32 hexColor );

// 32-bit hexidecimal color and alpha in RGBA format.
// - e.g. opaque red is 0xFF0000FF, half-transparent blue is 0x0000FF7F.
Color4B MakeColor4B( Uint32 hexColor );


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle

#endif // __BRITTLE_UTILS_STYLING_H
