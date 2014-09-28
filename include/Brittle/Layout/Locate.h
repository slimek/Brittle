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


private:
    
    Node* m_target { nullptr };
    Bool  m_applied { false };

    Vec2  m_location;
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
    m_location = Vec2( 0.5f, 0.5f );
    return *this;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle

#endif // __BRITTLE_LAYOUT_LOCATE_H
