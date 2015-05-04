// Brittle C++ Library - Nodes - Screen Cover Header

#ifndef __BRITTLE_NODES_SCREEN_COVER_H
#define __BRITTLE_NODES_SCREEN_COVER_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>
#include <2d/CCLayer.h>


namespace Brittle
{

///////////////////////////////////////////////////////////////////////////////
//
// Screen Cover
// - A LayerColor which is :
//   1. Child of screen. (i.e. Slibling of the Scene).
//   2. Size equals to the screen.
//   3. At the center of the screen.
//   4. In front of the Scene. (Z-order is 3 in the screen).
//   5. Swallows all touch events.
//
//   USAGE: Screen Cover can be the base class of a modal dialog.
//

class ScreenCover : public LayerColor
{
public:

    static ScreenCover* Create( SimpleScene* scene );

    Bool InitWithScene( SimpleScene* scene );

    virtual void Show() {}
    virtual void Hide() {}
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle

#endif // __BRITTLE_NODES_SCREEN_COVER_H
