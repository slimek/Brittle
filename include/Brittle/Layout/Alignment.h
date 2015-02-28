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
// Align Charm
//

class AlignCharm
{
public:
    explicit AlignCharm( Node* target );
    ~AlignCharm();

    void Apply();


    /// Align Method - Alignment ///

    AlignCharm& MiddleCenter();


protected:
    
    Node* m_target { nullptr };
    Bool  m_applied { false };

    Alignment m_alignment { ALIGNMENT_NONE };
};


inline AlignCharm Align( Node* target )
{
    return AlignCharm( target );
}


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

//
// Alignment
//

inline AlignmentValue Alignment::Vertical() const
{
    return static_cast< AlignmentValue >( m_value & ALIGNMENT_MASK_VERTICAL );
}


inline AlignmentValue Alignment::Horizontal() const
{
    return static_cast< AlignmentValue >( m_value & ALIGNMENT_MASK_HORIZONTAL );
}


//
// Align Charm
//

inline AlignCharm& AlignCharm::MiddleCenter()
{
    CARAMEL_ASSERT( m_alignment == ALIGNMENT_NONE );
    m_alignment = ALIGNMENT_MIDDLE_CENTER;
    return *this;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle

#endif // __BRITTLE_LAYOUT_ALIGNMENT_H
