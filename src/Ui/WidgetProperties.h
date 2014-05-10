// Brittle C++ Library - UI - Widget Properties Header

#ifndef __BRITTLE_UI_WIDGET_PROPERTIES_H
#define __BRITTLE_UI_WIDGET_PROPERTIES_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>
#include <Brittle/Utils/JsonValue.h>


namespace Brittle
{

///////////////////////////////////////////////////////////////////////////////
//
// Enumerations
//

enum StretchMethod
{
    STRETCH_NONE    = 0,  // Keep original size
    STRETCH_FIT     = 1,  // Keep ratio, fit the inside, may has border
    STRETCH_FILL    = 2,  // Keep ratio, fill the all screen, may be cropped
    STRETCH_STRETCH = 3,  // Stretch to all screen.
};


enum WidgetPropertiesFlags : Uint32
{
    WP_FLAG_USE_STRETCH_METHOD = 0x01,

    WP_FLAG_RECT_IS_SCENE      = 0x10000,
};


///////////////////////////////////////////////////////////////////////////////
//
// Widget Properties
// - For ui::Widget
//

struct WidgetProperties
{
    WidgetProperties()
        : stretchMethod( STRETCH_NONE )
        , flags( 0 )
    {}

    void Parse( const JsonValue& json );

    Vector2 position;

    StretchMethod stretchMethod;


    Uint32 flags;

private:

    void ParseRect( const JsonValue& json );
};


//
// Widget JSON Syntax
//
// size :
//   <stretch method>
//     "fit"  
//     "fill"
//     "stretch"
//   <special>
//     "scene"
//

///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle

#endif // __BRITTLE_UI_WIDGET_PROPERTIES_H
