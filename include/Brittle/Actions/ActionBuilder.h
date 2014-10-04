// Brittle C++ Library - Actions - Action Builder Header

#ifndef __BRITTLE_ACTIONS_ACTION_BUILDER_H
#define __BRITTLE_ACTIONS_ACTION_BUILDER_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>
#include <base/CCVector.h>
#include <functional>


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

    //
    // Clone / Retrieve
    //
    // - When calling these functions, a building spawn or sequence would
    //   compact into a single action.
    //

    ActionBuilder Clone();
    operator FiniteTimeAction*();


    /// Combination ///

    ActionBuilder& operator>>( ActionBuilder& next );
    ActionBuilder& operator+ ( ActionBuilder& peer );

    ActionBuilder& operator>>( ActionBuilder&& next );
    ActionBuilder& operator+ ( ActionBuilder&& peer );


    /// Decorators ///

    ActionBuilder& Target( Node* target );
    
    ActionBuilder& CompleteIf( std::function< Bool() > condition );

private:

    // Change a building spawn or sequence into a single action.
    void Compact();

    enum BuildingType
    {
        BUILDING_ACTION,
        BUILDING_SPAWN,
        BUILDING_SEQUENCE,
    };
    
    BuildingType m_type { BUILDING_ACTION };

    FiniteTimeAction* m_currAction { nullptr };
    Vector< FiniteTimeAction* > m_actions;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Actions

namespace Bta = Actions;

} // namespace Brittle

#endif // __BRITTLE_ACTIONS_ACTION_BUILDER_H
