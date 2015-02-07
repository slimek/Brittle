// Brittle C++ Library - Animation - Flipbook Animation Header

#ifndef __BRITTLE_ANIMATION_FLIPBOOK_ANIMATION_H
#define __BRITTLE_ANIMATION_FLIPBOOK_ANIMATION_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>


namespace Brittle
{

///////////////////////////////////////////////////////////////////////////////
//
// Flipbook Animation Builder
// - Build a vector of sprite frames from a series of texture files.
//
//   filePattern :
//     A path to the texture files. The {0} would be replaced by indexes.
//     It generates string according to Caramel.Format specifier.
//
//     Example:
//
//       "tex/orc_{0}.png"    > "tex/orc_0.png", "tex/orc_1.png", ...
//       "tex/orc_{0:D3}.png" > "tex/orc_000.png", "text/orc_001.png", ...
//

class FlipbookAnimationBuilder
{
public:

    typedef FlipbookAnimationBuilder Self;

    Self& Files( std::string filePattern, Uint numFrams );
    Self& Indexes( std::vector< Uint > indexes );
    Self& DelayPerUnit( float seconds );
    Self& UseAliasTexParameters();

    Animation* Build();

private:

    std::string m_filePattern;
    Uint m_numFrames { 0 };
    std::vector< Uint > m_indexes;
    Float m_delayPerUnit { 0 };  // Seconds
    Bool m_useAliasTexParameters { false };
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle

#endif // __BRITTLE_ANIMATION_FLIPBOOK_ANIMATION_H

