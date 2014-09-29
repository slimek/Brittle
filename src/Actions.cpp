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
    : m_type( BUILDING_ACTION )
    , m_currAction( action )
{
}


ActionBuilder ActionBuilder::Clone()
{
    this->Compact();
    return ActionBuilder( m_currAction->clone() );
}


ActionBuilder::operator FiniteTimeAction*()
{
    this->Compact();
    return m_currAction;
}


ActionBuilder& ActionBuilder::operator+( ActionBuilder& peer )
{
    switch ( m_type )
    {
    case BUILDING_SPAWN:
        m_actions.pushBack( peer );
        break;
    
    case BUILDING_SEQUENCE:
        this->Compact();
        // pass through ~~

    case BUILDING_ACTION:
        m_actions.pushBack( m_currAction );
        m_actions.pushBack( peer );
        m_type = BUILDING_SPAWN;
        break;

    default:
        CARAMEL_NOT_REACHED();
    }

    return *this;
}


ActionBuilder& ActionBuilder::operator>>( ActionBuilder& next )
{
    switch ( m_type )
    {
    case BUILDING_SEQUENCE:
        m_actions.pushBack( next );
        break;

    case BUILDING_SPAWN:
        this->Compact();
        // pass through ~~

    case BUILDING_ACTION:
        m_actions.pushBack( m_currAction );
        m_actions.pushBack( next );
        m_type = BUILDING_SEQUENCE;
        break;

    default:
        CARAMEL_NOT_REACHED();
    }

    return *this;
}


ActionBuilder& ActionBuilder::Target( Node* target )
{
    this->Compact();
    m_currAction = TargetedAction::create( target, m_currAction );
    return *this;
}


void ActionBuilder::Compact()
{
    switch ( m_type )
    {
    case BUILDING_ACTION:
        return;

    case BUILDING_SPAWN:
        m_currAction = Spawn::create( m_actions );
        m_actions.clear();
        m_type = BUILDING_ACTION;
        return;

    case BUILDING_SEQUENCE:
        m_currAction = Sequence::create( m_actions );
        m_actions.clear();
        m_type = BUILDING_ACTION;
        return;

    default:
        CARAMEL_NOT_REACHED();
    }
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Actions

} // namespace Brittle
