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
    STRETCH_STRETCH = 3,  // Stretch both dimensions to fit content area
};


enum WidgetPropertiesFlags : Uint32
{
    WP_FLAG_USE_STRETCH_METHOD  = 0x01,
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
    Uint32 flags;
    StretchMethod stretchMethod;

private:

    void ParseRect( const JsonValue& json );
    void ParseStretch( const JsonValue& json );
};


//
// Widget JSON Syntax
//
// "rect":
//   <coordiate>
//     "x y width height"
//   <stretchMethod>
//     "fit"
//     "fill"
//     "stretch"
//

///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle

#endif // __BRITTLE_UI_WIDGET_PROPERTIES_H
