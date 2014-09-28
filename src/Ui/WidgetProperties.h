// Brittle C++ Library - UI - Widget Properties Header

#ifndef __BRITTLE_UI_WIDGET_PROPERTIES_H
#define __BRITTLE_UI_WIDGET_PROPERTIES_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>
#include <Brittle/Layout/Stretch.h>
#include <Brittle/Utils/JsonValue.h>


namespace Brittle
{

///////////////////////////////////////////////////////////////////////////////
//
// Enumerations
//

enum WidgetPropertiesFlags : Uint32
{
    WP_FLAG_USE_STRETCH_METHOD  = 0x01,
    WP_FLAG_USE_WIDTH           = 0x02,
    WP_FLAG_USE_HEIGHT          = 0x04,
};


///////////////////////////////////////////////////////////////////////////////
//
// Widget Properties
// - For ui::Widget
//

struct WidgetProperties
{
    WidgetProperties()
        : flags( 0 )
        , visible( true )
        , zOrder( 0 )
        , anchor( Vec2::ANCHOR_MIDDLE )
        , stretchMethod( STRETCH_NONE )
    {}

    void Parse( const JsonValue& json );

    Uint32 flags;
    Bool visible;
    Int zOrder;

    
    /// Properties for Resize ///

    Vec2 position;
    Vec2 anchor;
    Size size;
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
//     "auto"
//

///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle

#endif // __BRITTLE_UI_WIDGET_PROPERTIES_H
