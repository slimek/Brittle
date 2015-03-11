// Brittle C++ Library - Enums - Alignment Header

#ifndef __BRITTLE_ENUMS_ALIGNMENT_H
#define __BRITTLE_ENUMS_ALIGNMENT_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>


namespace Brittle
{

///////////////////////////////////////////////////////////////////////////////
//
// Alignment Value
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


    /// Masks ///

    ALIGNMENT_MASK_VERTICAL   = 0x0F,
    ALIGNMENT_MASK_HORIZONTAL = 0xF0,
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

    // Partial values

    AlignmentValue Vertical()   const;
    AlignmentValue Horizontal() const;

private:
    AlignmentValue m_value { ALIGNMENT_NONE };
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

inline AlignmentValue Alignment::Vertical() const
{
    return static_cast< AlignmentValue >( m_value & ALIGNMENT_MASK_VERTICAL );
}


inline AlignmentValue Alignment::Horizontal() const
{
    return static_cast< AlignmentValue >( m_value & ALIGNMENT_MASK_HORIZONTAL );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle

#endif // __BRITTLE_ENUMS_ALIGNMENT_H
