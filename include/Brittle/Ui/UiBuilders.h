// Brittle C++ Library - UI - UI Builders Header

#ifndef __BRITTLE_UI_UI_BUILDERS_H
#define __BRITTLE_UI_UI_BUILDERS_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>


namespace Brittle
{

///////////////////////////////////////////////////////////////////////////////
//
// UI Builder Primitive Template
//

template< typename UiType >
class UiBuilder;


///////////////////////////////////////////////////////////////////////////////
//
// UI Builder for ui::Text
//

template<>
class UiBuilder< ui::Text >
{
    typedef UiBuilder< ui::Text > This;

public:

    UiBuilder()
        : m_text( ui::Text::create() )
    {}

    explicit UiBuilder( const std::string& text )
        : m_text( ui::Text::create() )
    {
        m_text->setString( text );
    }

    ui::Text* Build() const { return m_text; }

    This& FontSize( Int fontSize )
    {
        m_text->setFontSize( fontSize );
        return *this;
    }

    This& Color( const Color4B& color )
    {
        m_text->setTextColor( color );
        return *this;
    }

private:
    ui::Text* m_text { nullptr };
};


///////////////////////////////////////////////////////////////////////////////
//
// UI Builder for ui::Button
//

template<>
class UiBuilder< ui::Button >
{
    typedef UiBuilder< ui::Button > This;

public:

    UiBuilder( const std::string& normalImage )
        : m_button( ui::Button::create( normalImage ))
    {}

    ui::Button* Build() const { return m_button; }

    This& PressedAction( Bool enabled )
    {
        m_button->setPressedActionEnabled( enabled );
        return *this;
    }

    template< typename Function, typename Target >
    This& ClickEvent( const Function& func, const Target& target )
    {
        m_button->addClickEventListener(
            std::bind( func, target, std::placeholders::_1 ));
        return *this;
    }

private:
    ui::Button* m_button { nullptr };
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle

#endif // __BRITTLE_UI_UI_BUILDERS_H
