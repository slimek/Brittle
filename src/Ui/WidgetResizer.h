// Brittle C++ Library - UI - Widget Resizer Header

#ifndef __BRITTLE_UI_WIDGET_RESIZER_H
#define __BRITTLE_UI_WIDGET_RESIZER_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>
#include "Ui/WidgetAttributes.h"
#include <Brittle/Ui/UiTypes.h>


namespace Brittle
{

///////////////////////////////////////////////////////////////////////////////
//
// Widget Resizer
//

class WidgetResizer
{
public:
    WidgetResizer( ui::Widget* widget, const WidgetAttributes& attrs );
    virtual ~WidgetResizer() {}

    virtual void Resize( Node* parent );


private:

    ui::Widget* m_widget;
    WidgetAttributes m_attrs;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle

#endif // __BRITTLE_UI_WIDGET_RESIZER_H
