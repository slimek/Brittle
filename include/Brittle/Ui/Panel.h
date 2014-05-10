// Brittle C++ Library - UI - Panel Header

#ifndef __BRITTLE_UI_PANEL_H
#define __BRITTLE_UI_PANEL_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>
#include <Brittle/Ui/UiTypes.h>
#include <Brittle/Utils/JsonValue.h>
#include <Caramel/Error/Exception.h>
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

    // Throws if the child not found.
    ui::Widget* GetChild( const std::string& name ) const; 

    template< typename WidgetType >
    void GetChild( const std::string& name, WidgetType*& widget ) const;

    // Begins to layout when the parent is set.
    // - This only affects position and size.
    virtual void setParent( Node* parent ) override;

private:

    friend class PanelBuilder;
    friend class PanelResizer;

    JsonValue m_layoutJson;

    WidgetResizerPtr m_selfResizer;
    std::deque< WidgetResizerPtr > m_resizers;
};


//
// Implementation
//

template< typename WidgetType >
inline void Panel::GetChild( const std::string& name, WidgetType*& widget ) const
{
    widget = dynamic_cast< WidgetType* >( this->GetChild( name ));
    if ( ! widget )
    {
        CARAMEL_THROW( "Panel %s child %s convert failed",
                       this->getName(), name );
    }
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle

#endif // __BRITTLE_UI_PANEL_H
