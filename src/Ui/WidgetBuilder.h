// Brittle C++ Library - UI - Widget Builder Header

#ifndef __BRITTLE_UI_WIDGET_BUILDER_H
#define __BRITTLE_UI_WIDGET_BUILDER_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>
#include "Ui/WidgetAttributes.h"
#include <Brittle/Ui/UiTypes.h>
#include <JsonCpp/value.h>
#include <ui/UIWidget.h>


namespace Brittle
{

///////////////////////////////////////////////////////////////////////////////
//
// Widget Builder
//

class WidgetBuilder
{
public:
    
    WidgetBuilder( const Json::Value& json, const std::string& path );

    ui::Widget* GetWidget() const { return m_widget; }


private:

    void ReadNameAndType();
    void BuildWidgetByType();
    
    void ReadWidgetAttributes( WidgetAttributes& attrs );
    void FillWidgetAttributes( ui::Widget* widget, const WidgetAttributes& attrs );

    void BuildImageView();
    void BuildText();
    void BuildTextBMFont();

    Json::Value m_json;
    std::string m_path;
    std::string m_type;

    ui::Widget* m_widget;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle

#endif // __BRITTLE_UI_WIDGET_BUILDER_H
