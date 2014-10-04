// Brittle C++ Library - Actions - Action Wrappers Header

#ifndef __BRITTLE_ACTIONS_ACTION_WRAPPERS_H
#define __BRITTLE_ACTIONS_ACTION_WRAPPERS_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>
#include <2d/CCAction.h>
#include <functional>


namespace Brittle
{

///////////////////////////////////////////////////////////////////////////////
//
// Complete If
// - Observe a boolean. If it becomes true, the action complate immediately.
//

class CompleteIf : public FiniteTimeAction
{
public:
    
    static CompleteIf* Create(
        FiniteTimeAction* action, std::function< Bool() > condition );

    
    /// Overrides ///

    virtual CompleteIf* clone() const override;
    virtual CompleteIf* reverse() const override;
    virtual void startWithTarget( Node* targe ) override;
    virtual void stop() override;
    virtual void update( Float delta ) override;
    virtual Bool isDone() const override;


protected:
    
    CompleteIf() {}
    virtual ~CompleteIf();


private:

    FiniteTimeAction* m_innerAction { nullptr };
    std::function< Bool() > m_condition;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle

#endif // __BRITTLE_ACTIONS_ACTION_WRAPPERS_H
