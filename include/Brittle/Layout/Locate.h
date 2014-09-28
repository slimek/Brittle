// Brittle C++ Library - Layout - Locate Header

#ifndef __BRITTLE_LAYOUT_LOCATE_H
#define __BRITTLE_LAYOUT_LOCATE_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>
#include <Caramel/Error/Assert.h>
#include <2d/CCNode.h>


namespace Brittle
{

///////////////////////////////////////////////////////////////////////////////
//
// Locate Charm
//

class LocateCharm
{
public:
    explicit LocateCharm( Node* target );
    ~LocateCharm();

    void Apply();


    /// Position ///

    LocateCharm& Center();

    LocateCharm& FromLeft  ( Float width );
    LocateCharm& FromRight ( Float width );
    LocateCharm& FromTop   ( Float height );
    LocateCharm& FromBottom( Float height );


private:
    
    Node* m_target { nullptr };
    Bool  m_applied { false };

    enum UseFlag
    {
        USE_X_NORM          = 0x01,  // 0.0 - 1.0
        USE_X_FROM_LEFT     = 0x02,
        USE_X_FROM_RIGHT    = 0x04,

        USE_Y_NORM          = 0x10,  // 0.0 - 1.0
        USE_Y_FROM_TOP      = 0x20,
        USE_Y_FROM_BOTTOM   = 0x40,
    };

    Uint32 m_uses { 0 };

    Float m_paramX { 0 };
    Float m_paramY { 0 };
};


inline LocateCharm Locate( Node* target )
{
    return LocateCharm( target );
}


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

inline LocateCharm& LocateCharm::Center()
{
    m_uses = USE_X_NORM | USE_Y_NORM;
    m_paramX = 0.5;
    m_paramY = 0.5;
    return *this;
}


inline LocateCharm& LocateCharm::FromLeft( Float width )
{   
    m_uses |= USE_X_FROM_LEFT;
    m_paramX = width;
    return *this;
}


inline LocateCharm& LocateCharm::FromRight( Float width )
{   
    m_uses |= USE_X_FROM_RIGHT;
    m_paramX = width;
    return *this;
}


inline LocateCharm& LocateCharm::FromTop( Float height )
{
    m_uses |= USE_Y_FROM_TOP;
    m_paramY = height;
    return *this;
}


inline LocateCharm& LocateCharm::FromBottom( Float height )
{
    m_uses |= USE_Y_FROM_BOTTOM;
    m_paramY = height;
    return *this;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle

#endif // __BRITTLE_LAYOUT_LOCATE_H
