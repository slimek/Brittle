// Brittle C++ Library - Actions - Skippable Sequence Header

#ifndef __BRITTLE_ACTIONS_SKIPPABLE_SEQUENCE_H
#define __BRITTLE_ACTIONS_SKIPPABLE_SEQUENCE_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>
#include <2d/CCAction.h>


namespace Brittle
{

///////////////////////////////////////////////////////////////////////////////
//
// Skippable Sequence
//

class SkippableSequence : public Sequence
{
public:

    static SkippableSequence* Create( const Vector< FiniteTimeAction* >& arrayOfAction );

    static SkippableSequence* CreateWithTwoActions(
        FiniteTimeAction* action0, FiniteTimeAction* action1 );


    /// Overrides ///

    virtual void update( float t ) override;
    virtual bool isDone() const override;

protected:

};


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle

#endif // __BRITTLE_ACTIONS_SKIPPABLE_SEQUENCE_H
