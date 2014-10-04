// Brittle C++ Library - Actions - Empty Action Header

#ifndef __BRITTLE_ACTIONS_EMPTY_ACTION_H
#define __BRITTLE_ACTIONS_EMPTY_ACTION_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>
#include <2d/CCAction.h>


namespace Brittle
{

///////////////////////////////////////////////////////////////////////////////
//
// Empty Action
// - A valid action which does nothing, done immediately.
//

class EmptyAction : public FiniteTimeAction
{
public:
    
    static EmptyAction* Create();

    /// Overrides ////

    virtual EmptyAction* clone() const override;
    virtual EmptyAction* reverse() const override;
    virtual void update( Float time ) override;
    virtual void step( Float detla ) override;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle

#endif // __BRITTLE_ACTIONS_EMPTY_ACTION_H
