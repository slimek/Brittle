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
    STRETCH_STRETCH = 3,  // Stretch both dimensions to fit content area
    STRETCH_AUTO    = 4,  // Expand as large as possible, depends on the Panel's type.
};


///////////////////////////////////////////////////////////////////////////////
//
// Stretch Charm
//

class StretchCharm : public AlignmentCharm< StretchCharm >
{
public:
    explicit StretchCharm( Node* target );
    virtual ~StretchCharm();

    virtual void Apply();

    /// Stretch Mothod ///

    StretchCharm& Fill();
    StretchCharm& Fit();


protected:

    Node* m_target { nullptr };
    Bool  m_applied { false };

    StretchMethod m_stretchMethod { STRETCH_UNDEF };
};

inline StretchCharm Stretch( Node* target )
{
    return StretchCharm( target );
}


//class StretchWidgetCharm : public StretchCharm
//{
//public:
//    StretchWidgetCharm( ui::Widget* target );
//
//    void Apply() override;
//
//
//private:
//    
//    ui::Widget* m_target { nullptr };
//
//};


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


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle

#endif // __BRITTLE_LAYOUT_STRETCH_H
