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

class ActionBuilder
{
public:

    explicit ActionBuilder( FiniteTimeAction* action );

    operator Sequence*() const;

private:

    Vector< FiniteTimeAction* > m_actions;
    FiniteTimeAction* m_lastAction;
};


} // namespace Actions

namespace Bta = Actions;

} // namespace Brittle

#endif // __BRITTLE_ACTIONS_ACTION_BUILDER_H
