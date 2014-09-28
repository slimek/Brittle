// Brittle C++ Library - Layout - Alignment Header

#ifndef __BRITTLE_LAYOUT_ALIGNMENT_H
#define __BRITTLE_LAYOUT_ALIGNMENT_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>
#include <Caramel/Error/Assert.h>
#include <base/ccTypes.h>


namespace Brittle
{

///////////////////////////////////////////////////////////////////////////////
//
// Alignment Value enum
//

enum AlignmentValue
{
    ALIGNMENT_NONE      = 0,


    /// Single Flag ///

    ALIGNMENT_LEFT      = 0x01,
    ALIGNMENT_CENTER    = 0x02,
    ALIGNMENT_RIGHT     = 0x04,

    ALIGNMENT_TOP       = 0x10,
    ALIGNMENT_MIDDLE    = 0x20,
    ALIGNMENT_BOTTOM    = 0x40,

    
    /// Combination Flags ///

    ALIGNMENT_MIDDLE_CENTER = ALIGNMENT_MIDDLE | ALIGNMENT_CENTER,
};


///////////////////////////////////////////////////////////////////////////////
//
// Alignment
//

class Alignment
{
public:
    Alignment() {}
    Alignment( AlignmentValue value ) : m_value( value ) {}

    operator AlignmentValue() const { return m_value; }

private:
    AlignmentValue m_value { ALIGNMENT_NONE };
};


///////////////////////////////////////////////////////////////////////////////
//
// Alignment Charm
//

template< typename Derived >
class AlignmentCharm
{
public:

    Derived& MiddleCenter();

protected:
    
    Alignment m_alignment;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

template< typename Derived >
inline Derived& AlignmentCharm< Derived >::MiddleCenter()
{
    CARAMEL_ASSERT( m_alignment == ALIGNMENT_NONE );
    m_alignment = ALIGNMENT_MIDDLE_CENTER;
    return static_cast< Derived& >( *this );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle

#endif // __BRITTLE_LAYOUT_ALIGNMENT_H
