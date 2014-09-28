// Brittle C++ Library - Actions - Interval Actions Header

#ifndef __BRITTLE_ACTIONS_INTERVAL_ACTIONS_H
#define __BRITTLE_ACTIONS_INTERVAL_ACTIONS_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>
#include <Brittle/Actions/ActionBuilder.h>
#include <2d/CCActionInterval.h>


namespace Brittle
{

namespace Actions
{

inline ActionBuilder MoveTo( Float duration, Float x, Float y )
{
    auto moveTo = MoveTo::create( duration, Vec2( x, y ));
    return ActionBuilder( moveTo );
}


inline ActionBuilder RotateBy( Float duration, Float deltaAngle )
{
    auto rotateBy = RotateBy::create( duration, deltaAngle );
    return ActionBuilder( rotateBy );
}


inline ActionBuilder ScaleTo( Float duration, Float scale )
{
    auto scaleTo = ScaleTo::create( duration, scale );
    return ActionBuilder( scaleTo );
}


} // namespace Actions

namespace Bta = Actions;

} // namespace Brittle

#endif // __BRITTLE_ACTIONS_INTERVAL_ACTIONS_H
