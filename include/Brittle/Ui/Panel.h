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

    // Throws if the child not found.
    ui::Widget* GetChild( const std::string& name ) const; 

    template< typename WidgetType >
    void GetChild( const std::string& name, WidgetType*& widget ) const;

    // Begins to layout when the parent is set.
    // - This only affects position and size.
    virtual void setParent( Node* parent ) override;


    /// Child UI Event Handling ///

    void SetClickHandler( const std::string& name, ClickHandler&& handler ); 

    template< typename Function, typename T >
    void SetClickHandler( const std::string& name, const Function& handler, T* receiver );


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
        CARAMEL_THROW( "Panel %s child %s convert failed",
                       this->getName(), name );
    }
}


template< typename Function, typename T >
inline void Panel::SetClickHandler( const std::string& name, const Function& handler, T* receiver )
{
    namespace sp = std::placeholders;

    this->SetClickHandler( name, std::bind( handler, receiver, sp::_1 ));
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle

#endif // __BRITTLE_UI_PANEL_H
