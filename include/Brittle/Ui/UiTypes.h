// Brittle C++ Library - UI - UI Basic Types Header

#ifndef __BRITTLE_UI_UI_TYPES_H
#define __BRITTLE_UI_UI_TYPES_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>


namespace Brittle
{

///////////////////////////////////////////////////////////////////////////////
//
// Brittle Forwards Declaration
//

// UI Components

class Panel;
class SimpleButton;


// UI Event Handlers
typedef std::function< void( Ref* ) > ClickHandler;


// UI Internal Utilities

class WidgetResizer;
typedef std::shared_ptr< WidgetResizer > WidgetResizerPtr;


///////////////////////////////////////////////////////////////////////////////
//
// Brittle UI Interfaces
//

struct Clickable
{
    virtual ~Clickable() {}

    virtual void SetClickHandler( ClickHandler&& handler ) = 0;
};



///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle


///////////////////////////////////////////////////////////////////////////////
//
// cocos2d::ui Forwards Declaration
//

namespace cocos2d { namespace ui
{

class Widget;
class ImageView;
class Text;
class TextBMFont;

} } // namespace cocos2d::ui


///////////////////////////////////////////////////////////////////////////////

#endif // __BRITTLE_UI_UI_TYPES_H
