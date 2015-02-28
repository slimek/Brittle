// Brittle C++ Library - Layout - Stretch Header

#ifndef __BRITTLE_LAYOUT_STRETCH_H
#define __BRITTLE_LAYOUT_STRETCH_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>
#include <Brittle/Layout/Alignment.h>
#include <Caramel/Error/Assert.h>
#include <2d/CCNode.h>


namespace Brittle
{

///////////////////////////////////////////////////////////////////////////////
//
// Stretch Method
//

enum StretchMethod
{
    STRETCH_UNDEF   = -1,

    STRETCH_NONE    = 0,  // Keep original size
    STRETCH_FIT     = 1,  // Keep ratio, fit the inside, may has border
    STRETCH_FILL    = 2,  // Keep ratio, fill the all screen, may be cropped
    STRETCH_AUTO    = 3,  // Stretch both dimensions to fit content area, may distort the ratio

    // Available for Sprites

    STRETCH_REPEAT  = 4,  // Repeat the sprite's texture to fill the content area
};


///////////////////////////////////////////////////////////////////////////////
//
// Stretch Charm
// - Stretch a node the fill its parent with specified method.
//

class StretchCharm
{
public:
    explicit StretchCharm( Node* target );
    ~StretchCharm();

    void Apply();

    /// Stretch Mothod - General ///

    StretchCharm& Fill();
    StretchCharm& Fit();
    StretchCharm& Auto();

    // Stretch for Sprites
    // - Throws if the target is not a sprite
    StretchCharm& Repeat();


protected:

    /// Stretch Methods ///

    void ApplyAuto();
    void ApplyRepeat();


    /// Data Members ///

    Node* m_target { nullptr };
    Bool  m_applied { false };

    StretchMethod m_stretchMethod { STRETCH_UNDEF };
};

inline StretchCharm Stretch( Node* target )
{
    return StretchCharm( target );
}


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

inline StretchCharm& StretchCharm::Fill()
{
    CARAMEL_ASSERT( m_stretchMethod == STRETCH_UNDEF );    
    m_stretchMethod = STRETCH_FILL;
    return *this;
}


inline StretchCharm& StretchCharm::Fit()
{
    CARAMEL_ASSERT( m_stretchMethod == STRETCH_UNDEF );    
    m_stretchMethod = STRETCH_FIT;
    return *this;
}


inline StretchCharm& StretchCharm::Repeat()
{
    CARAMEL_ASSERT( m_stretchMethod == STRETCH_UNDEF );
    m_stretchMethod = STRETCH_REPEAT;
    return *this;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle

#endif // __BRITTLE_LAYOUT_STRETCH_H
