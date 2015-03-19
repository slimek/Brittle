// Brittle C++ Library - UI - Panel Header

#ifndef __BRITTLE_UI_PANEL_H
#define __BRITTLE_UI_PANEL_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>
#include <Brittle/Ui/UiTypes.h>
#include <Brittle/Utils/JsonValue.h>
#include <Caramel/Error/Exception.h>
#include <ui/UIWidget.h>
#include <functional>


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


    /// Accessors ///

    // Throws if the child not found.
    Node* GetChild( const std::string& name ) const; 
    Node* GetDescendant( const std::string& name ) const;

    template< typename WidgetType >
    void GetChild( const std::string& name, WidgetType*& widget ) const;


    /// Node Event Handling ///

    // Begins to layout when the parent is set.
    // - This only affects position and size.
    virtual void setParent( Node* parent ) override;


    /// Children UI Event Handling ///

    void SetClickHandler( const std::string& name, ClickHandler handler ); 


private:

    /// Data Members ///

    friend class PanelBuilder;
    friend class PanelResizer;

    JsonValue m_layoutJson;

    // The root panel needs to resize itself.
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
        CARAMEL_THROW( "Panel {0} child {1} convert failed",
                       this->getName(), name );
    }
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle

#endif // __BRITTLE_UI_PANEL_H
