// Brittle C++ Library - UI - Panel Builder Header

#ifndef __BRITTLE_UI_PANEL_BUILDER_H
#define __BRITTLE_UI_PANEL_BUILDER_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>
#include <Brittle/Ui/UiTypes.h>
#include <JsonCpp/value.h>


namespace Brittle
{

///////////////////////////////////////////////////////////////////////////////
//
// Panel Builder
//

class PanelBuilder
{
public:

    explicit PanelBuilder( const std::string& layoutPath );

    Panel* GetPanel() const { return m_panel; }

private:

    void LoadJsonRoot();
    void BuildWidgets();

    std::string m_layoutPath;

    Json::Value m_rootJson;

    Panel* m_panel;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle

#endif // __BRITTLE_UI_PANEL_BUILDER_H
