// Brittle C++ Library - Actions Implementation

#include "BrittlePch.h"

#include <Brittle/Actions/ActionBuilder.h>
#include <Brittle/Actions/ActionWrappers.h>
#include <Brittle/Actions/EmptyAction.h>
#include <Brittle/Actions/SkippableSequence.h>


namespace Brittle
{

namespace Actions
{

//
// [Contents]
//
//   ActionBuilder
//   CompleteIf
//   SkippableSequence
//   EmptyAction
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


//
// Combinations
//

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


ActionBuilder& ActionBuilder::operator+( ActionBuilder&& peer )
{
    return this->operator+( peer );
}


ActionBuilder& ActionBuilder::operator>>( ActionBuilder&& next )
{
    return this->operator>>( next );
}


//
// Decorators
//

ActionBuilder& ActionBuilder::Target( Node* target )
{
    this->Compact();
    m_currAction = TargetedAction::create( target, m_currAction );
    return *this;
}


ActionBuilder& ActionBuilder::CompleteIf( std::function< Bool() > condition )
{
    this->Compact();
    m_currAction = CompleteIf::Create( m_currAction, condition );
    return *this;
}


//
// Internal Functions
//

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
        m_currAction = SkippableSequence::Create( m_actions );
        m_actions.clear();
        m_type = BUILDING_ACTION;
        return;

    default:
        CARAMEL_NOT_REACHED();
    }
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Actions


///////////////////////////////////////////////////////////////////////////////
//
// Complete When
//

CompleteIf* CompleteIf::Create( FiniteTimeAction* action, std::function< Bool() > condition )
{
    auto complete = new CompleteIf;
    complete->setDuration( action->getDuration() );
    complete->m_innerAction = action;
    complete->m_condition = condition;
    complete->autorelease();
    action->retain();
    return complete;
}


CompleteIf::~CompleteIf()
{
    m_innerAction->release();
}


CompleteIf* CompleteIf::clone() const
{
    return Create( m_innerAction, m_condition );
}


CompleteIf* CompleteIf::reverse() const
{
    CARAMEL_NOT_IMPLEMENTED();
}


void CompleteIf::startWithTarget( Node* target )
{
    this->FiniteTimeAction::startWithTarget( target );
    m_innerAction->startWithTarget( target );
}


void CompleteIf::stop()
{
    m_innerAction->stop();
    this->FiniteTimeAction::stop();
}


void CompleteIf::update( Float delta )
{
    if ( m_condition() )
    {
        m_innerAction->update( 1.0 );
    }
    else
    {
        m_innerAction->update( delta );
    }
}


Bool CompleteIf::isDone() const
{
    return m_innerAction->isDone();
}


///////////////////////////////////////////////////////////////////////////////
//
// Skippable Sequence
//

SkippableSequence* SkippableSequence::Create( const Vector< FiniteTimeAction* >& arrayOfActions )
{
    if ( arrayOfActions.empty() )
    {
        CARAMEL_ALERT( "Array of actions is empty" );
        return SkippableSequence::CreateWithTwoActions(
            EmptyAction::Create(), EmptyAction::Create() );
    }

    auto count = arrayOfActions.size();
    auto prev = arrayOfActions.at( 0 );
    
    if ( count > 1 )
    {
        for ( Int i = 1; i < count; ++ i )
        {
            prev = CreateWithTwoActions( prev, arrayOfActions.at( i ));
        }
    }
    else
    {
        prev = CreateWithTwoActions( prev, EmptyAction::Create() );
    }
    
    return static_cast< SkippableSequence* >( prev );
}


SkippableSequence* SkippableSequence::CreateWithTwoActions(
    FiniteTimeAction* action0, FiniteTimeAction* action1 )
{
    auto sequence = new SkippableSequence;
    sequence->initWithTwoActions( action0, action1 );
    sequence->autorelease();
    return sequence;
}


void SkippableSequence::update( Float t )
{
    float newT = 0.0f;

    if ( _last == -1 )
    {
        // First update

        _actions[0]->startWithTarget( _target );

        if ( t < _split )
        {
            _last = 0;
        }
        else
        {
            // Jump to action 1

            _last = 1;

            _actions[0]->update( 1.0f );
            _actions[0]->stop();
            _actions[1]->startWithTarget( _target );
        }
    }

    if ( _last == 0 )
    {
        if ( t < _split )
        {
            if ( _split == 0 )
            {
                newT = 1; 
            }
            else
            {
                newT = t / _split;
            }

            _actions[0]->update( newT );
        }
        else
        {
            // Continue to action 1

            _last = 1;

            _actions[0]->update( 1.0f );
            _actions[0]->stop();
            _actions[1]->startWithTarget( _target );
        }
    }

    if ( _last == 1 )
    {
        if ( _split == 1 )
        {
            newT = 1;
        }
        else
        {
            newT = ( t - _split ) / ( 1 - _split );
        }

        _actions[1]->update( newT );
    }
}


Bool SkippableSequence::isDone() const
{
    return _actions[0]->isDone() && _actions[1]->isDone();
}


///////////////////////////////////////////////////////////////////////////////
//
// Empty Action
//

EmptyAction* EmptyAction::Create()
{
    auto act = new EmptyAction;
    act->autorelease();
    return act;
}


EmptyAction* EmptyAction::clone() const
{
    // Nothing to be copied.
    return Create();
}


EmptyAction* EmptyAction::reverse() const
{
    // Nothing to be copied.
    return Create();
}


void EmptyAction::update( Float )
{
}


void EmptyAction::step( Float )
{
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle
