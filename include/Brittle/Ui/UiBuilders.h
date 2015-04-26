// Brittle C++ Library - UI - UI Builders Header

#ifndef __BRITTLE_UI_UI_BUILDERS_H
#define __BRITTLE_UI_UI_BUILDERS_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>
#include <Brittle/Layout/Align.h>
#include <Brittle/Utils/Styling.h>


namespace Brittle
{

///////////////////////////////////////////////////////////////////////////////
//
// Builder for ui::Text
//

class UiTextBuilder
{
public:

    UiTextBuilder()
        : m_text( ui::Text::create() )
    {}

    explicit UiTextBuilder( const std::string& text )
        : m_text( ui::Text::create() )
    {
        m_text->setString( text );
    }

    UiTextBuilder( const std::string& text, const FontStyle& font )
        : m_text( ui::Text::create() )
    {
        m_text->setString( text );
        this->Font( font );
    }


    ui::Text* Build()    const { return m_text; }
    operator ui::Text*() const { return m_text; }


    UiTextBuilder& Font( const FontStyle& font )
    {
        m_text->setFontSize( font.size );
        m_text->setTextColor( font.color );
        if ( ! font.name.empty() )
        {
            m_text->setFontName( font.name );
        }
        return *this;
    }


    UiTextBuilder& FontSize( Int fontSize )
    {
        m_text->setFontSize( fontSize );
        return *this;
    }

    UiTextBuilder& Color( const Color4B& color )
    {
        m_text->setTextColor( color );
        return *this;
    }

    UiTextBuilder& Color( const Color3B& color )
    {
        m_text->setTextColor( Color4B( color ));
        return *this;
    }


private:
    ui::Text* m_text { nullptr };
};


///////////////////////////////////////////////////////////////////////////////
//
// Builder for ui::Button
//

class UiButtonBuilder
{
public:

    UiButtonBuilder( const std::string& normalImage )
        : m_button( ui::Button::create( normalImage ))
    {}


    ui::Button* Build()    const { return m_button; }
    operator ui::Button*() const { return m_button; }


    UiButtonBuilder& PressedAction( Bool enabled )
    {
        m_button->setPressedActionEnabled( enabled );
        return *this;
    }

    template< typename Function, typename Target, typename... Args >
    UiButtonBuilder& ClickEvent( const Function& func, const Target& target, const Args&... args )
    {
        m_button->addClickEventListener(
            std::bind( func, target, std::placeholders::_1, args... ));
        return *this;
    }

    // Put a text at the center of the Button.
    UiButtonBuilder& Text( ui::Text* text )
    {
        m_button->setCascadeOpacityEnabled( true );
        m_button->addChild( text );
        Locate( text ).Center();
        return *this;
    }


private:
    ui::Button* m_button { nullptr };
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle

#endif // __BRITTLE_UI_UI_BUILDERS_H
