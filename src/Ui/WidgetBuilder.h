// Brittle C++ Library - UI - Widget Builder Header

#ifndef __BRITTLE_UI_WIDGET_BUILDER_H
#define __BRITTLE_UI_WIDGET_BUILDER_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>
#include "Ui/WidgetProperties.h"
#include <Brittle/Ui/UiTypes.h>
#include <Brittle/Utils/JsonValue.h>
#include <ui/UIWidget.h>
#include <boost/optional.hpp>


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

    ui::Widget*      GetWidget()     const { return m_widget; }
    WidgetProperties GetProperties() const { return m_props; }


private:

    void ReadNameAndType();
    void BuildWidgetByType();
    
    void FillWidgetName( ui::Widget* widget );

    void BuildImageView();
    void BuildText();
    void BuildTextBMFont();
    void BuildPanel();

    JsonValue m_json;

    std::string m_path;
    std::string m_type;

    boost::optional< std::string > m_name;

    ui::Widget* m_widget;
    WidgetProperties m_props;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle

#endif // __BRITTLE_UI_WIDGET_BUILDER_H
