// Brittle C++ Library - Layout - Align Header

#ifndef __BRITTLE_LAYOUT_ALIGN_H
#define __BRITTLE_LAYOUT_ALIGN_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>
#include <Brittle/Enums/Alignment.h>
#include <Caramel/Error/Assert.h>


namespace Brittle
{

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

inline AlignCharm& AlignCharm::MiddleCenter()
{
    CARAMEL_ASSERT( m_alignment == ALIGNMENT_NONE );
    m_alignment = ALIGNMENT_MIDDLE_CENTER;
    return *this;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle

#endif // __BRITTLE_LAYOUT_ALIGN_H
