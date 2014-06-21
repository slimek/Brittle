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
    m_actions.pushBack( action );
}


ActionBuilder::operator Sequence*() const
{
    return Sequence::create( m_actions );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Actions

} // namespace Brittle
