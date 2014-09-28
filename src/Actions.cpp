// Brittle C++ Library - Actions Implementation

#include "BrittlePch.h"

#include <Brittle/Actions/ActionBuilder.h>


namespace Brittle
{

namespace Actions
{

//
// [Contents]
//
//   ActionBuilder
//

///////////////////////////////////////////////////////////////////////////////
//
// Action Builder
//

ActionBuilder::ActionBuilder( FiniteTimeAction* action )
    : m_lastAction( action )
{
}


ActionBuilder ActionBuilder::Clone() const
{
    ActionBuilder builder( m_lastAction->clone() );

    for ( auto a : m_actions )
    {
        builder.m_actions.pushBack( a->clone() );
    }

    return builder;
}


ActionBuilder::operator Sequence*()
{
    m_actions.pushBack( m_lastAction );
    return Sequence::create( m_actions );
}


//ActionBuilder& ActionBuilder::operator+( ActionBuilder& peer )
//{
//    return *this;
//}


ActionBuilder& ActionBuilder::operator>>( ActionBuilder& next )
{
    m_actions.pushBack( m_lastAction );
    m_actions.pushBack( next.m_actions );
    m_lastAction = next.m_lastAction;
    return *this;
}


ActionBuilder& ActionBuilder::Target( Node* target )
{
    m_lastAction = TargetedAction::create( target, m_lastAction );
    return *this;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Actions

} // namespace Brittle
