// Brittle C++ Library - UI - Panel Header

#ifndef __BRITTLE_UI_PANEL_H
#define __BRITTLE_UI_PANEL_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>
#include <Brittle/Ui/UiTypes.h>
#include <ui/UIWidget.h>


namespace Brittle
{

///////////////////////////////////////////////////////////////////////////////
//
// Panel
//

class Panel : public ui::Widget
{
public:

    static Panel* Create( const std::string& layoutPath );
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle

#endif // __BRITTLE_UI_PANEL_H
