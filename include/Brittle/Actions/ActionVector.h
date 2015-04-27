// Brittle C++ Library - Actions - Action Vector Header

#ifndef __BRITTLE_ACTIONS_ACTION_VECTOR_H
#define __BRITTLE_ACTIONS_ACTION_VECTOR_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>
#include <2d/CCActionInterval.h>
#include <initializer_list>


namespace Brittle
{

///////////////////////////////////////////////////////////////////////////////
//
// Action Vector
// - Supports Vector< FiniteTimeAction* > with std::initializer_list.
//

class ActionVector : public Vector< FiniteTimeAction* >
{
public:
    
    ActionVector() {}

    explicit ActionVector( Usize capacity );
    ActionVector( std::initializer_list< FiniteTimeAction* > actions );
};


///////////////////////////////////////////////////////////////////////////////
//
// Sequence Of
// - Create a Sequence with std::initializer_list.
//

class SequenceOf
{
public:

    explicit SequenceOf( std::initializer_list< FiniteTimeAction* > actions );

    operator Sequence*() const { return m_sequence; }

private:

    Sequence* m_sequence { nullptr };
};


///////////////////////////////////////////////////////////////////////////////
//
// Spawn Of
// - Create a Spawn with std::initializer_list.
//

class SpawnOf
{
public:

    explicit SpawnOf( std::initializer_list< FiniteTimeAction* > actions );

    operator Spawn*() const { return m_spawn; }

private:

    Spawn* m_spawn { nullptr };
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

inline SequenceOf::SequenceOf( std::initializer_list< FiniteTimeAction* > actions )
{
    const ActionVector vec( std::move( actions ));
    m_sequence = Sequence::create( vec );
}


inline SpawnOf::SpawnOf( std::initializer_list< FiniteTimeAction* > actions )
{
    const ActionVector vec( std::move( actions ));
    m_spawn = Spawn::create( vec );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle

#endif // __BRITTLE_ACTIONS_ACTION_VECTOR_H
