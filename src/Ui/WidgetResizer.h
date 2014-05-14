// Brittle C++ Library - UI - Widget Resizer Header

#ifndef __BRITTLE_UI_WIDGET_RESIZER_H
#define __BRITTLE_UI_WIDGET_RESIZER_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>
#include "Ui/WidgetProperties.h"
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
    WidgetResizer( ui::Widget* widget, const WidgetProperties& props );
    virtual ~WidgetResizer() {}

    virtual void Resize( const Rect& area );

protected:

    void StretchWithScale( const Rect& area );
    void StretchWithSize( const Rect& area );

    void ResizeWithScale();
    void ResizeWithSize();

    ui::Widget* m_widget;
    WidgetProperties m_props;
};


///////////////////////////////////////////////////////////////////////////////
//
// Panel Resizer
//

class PanelResizer : public WidgetResizer
{
public:
    PanelResizer( Panel* panel, const WidgetProperties& props );

    void Resize( const Rect& area ) override;

private:

    Panel* m_panel;
};

///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle

#endif // __BRITTLE_UI_WIDGET_RESIZER_H
