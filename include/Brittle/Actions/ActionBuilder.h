// Brittle C++ Library - Actions - Action Builder Header

#ifndef __BRITTLE_ACTIONS_ACTION_BUILDER_H
#define __BRITTLE_ACTIONS_ACTION_BUILDER_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>
#include <base/CCVector.h>


namespace Brittle
{

namespace Actions
{

///////////////////////////////////////////////////////////////////////////////
//
// Action Builder
//

class ActionBuilder
{
public:

    explicit ActionBuilder( FiniteTimeAction* action );

    operator Sequence*();

    ActionBuilder& operator>>( ActionBuilder& next );

    ActionBuilder& Target( Node* target );

private:

    Vector< FiniteTimeAction* > m_actions;
    FiniteTimeAction* m_lastAction { nullptr };
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Actions

namespace Bta = Actions;

} // namespace Brittle

#endif // __BRITTLE_ACTIONS_ACTION_BUILDER_H
