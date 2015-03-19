// Brittle C++ Library - UI Implementation

#include "BrittlePch.h"

#include "Ui/PanelBuilder.h"
#include "Ui/WidgetBuilder.h"
#include "Ui/WidgetProperties.h"
#include "Ui/WidgetResizer.h"
#include <Brittle/Ui/LabelButton.h>
#include <Brittle/Ui/Panel.h>
#include <Brittle/Ui/SimpleButton.h>
#include <Brittle/Utils/Geometry.h>
#include <Macaron/RapidJson/JsonReader.h>
#include <Caramel/Data/LookupTable.h>
#include <Caramel/FileSystem/Path.h>


namespace Brittle
{

//
// Content
//
//   LabelButton
//   SimpleButton
//   Panel
//   PanelBuilder
//   WidgetBuilder
//   WidgetResizer
//   PanelResizer
//   WidgetProperties
//

///////////////////////////////////////////////////////////////////////////////
//
// Label Button
//

LabelButton::LabelButton()
{
    this->setTouchEnabled( true );

    this->addTouchEventListener( CC_CALLBACK_2( LabelButton::OnTouchEvent, this ));
}


LabelButton* LabelButton::Create()
{
    auto button = new LabelButton;
    if ( button->init() )
    {
        button->autorelease();
        return button;
    }
    CC_SAFE_DELETE( button );
    return nullptr;
}


void LabelButton::SetClickHandler( ClickHandler handler )
{
    m_clickHandler = std::move( handler );
}   


void LabelButton::OnTouchEvent( Ref* sender, TouchEventType type )
{
    switch ( type )
    {
    case TouchEventType::ENDED:
    {
        if ( m_clickHandler )
        {
            m_clickHandler( this );
        }
        break;
    }

    default:
        ;
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// Simple Button
//

SimpleButton::SimpleButton()
{
    this->addTouchEventListener( CC_CALLBACK_2( SimpleButton::OnTouchEvent, this ));
}


SimpleButton* SimpleButton::Create()
{
    auto button = new SimpleButton;
    if ( button->init() )
    {
        button->autorelease();
        return button;
    }
    CC_SAFE_DELETE( button );
    return nullptr;
}


SimpleButton* SimpleButton::Create(
    const std::string& normalImage, const std::string& selectedImage,
    const std::string& disabledImage, TextureResType texType )
{
    auto button = new SimpleButton;
    if ( button->init( normalImage, selectedImage, disabledImage, texType ))
    {
        button->autorelease();
        return button;
    }
    CC_SAFE_DELETE( button );
    return nullptr;
}


void SimpleButton::SetClickHandler( ClickHandler handler )
{
    m_clickHandler = std::move( handler );
}   


void SimpleButton::OnTouchEvent( Ref* sender, TouchEventType type )
{
    switch ( type )
    {
    case TouchEventType::ENDED:
        if ( m_clickHandler )
        {
            m_clickHandler( this );
        }
        break;
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// Panel
//

Panel* Panel::Create( const std::string& layoutPath )
{
    PanelBuilder builder( layoutPath, true );
    return builder.GetPanel();
}


Node* Panel::GetChild( const std::string& name ) const
{
    auto widget = this->getChildByName( name );
    if ( ! widget )
    {
        CARAMEL_THROW( "Panel \"{0}\" child \"{1}\" not found", this->getName(), name );
    }
    return widget;
}


Node* Panel::GetDescendant( const std::string& name ) const
{
    auto widget = this->getChildByName( name );
    if ( widget ) { return widget; }

    for ( auto node : this->getChildren() )
    {
        auto panel = dynamic_cast< Panel* >( node );
        if ( panel )
        {
            widget = panel->GetDescendant( name );
            if ( widget ) { return widget; }
        }
    }

    CARAMEL_THROW( "Panel \"{0}\" descendant \"{1}\" not found", this->getName(), name );
}


void Panel::setParent( Node* parent )
{
    this->ui::Widget::setParent( parent );

    if ( nullptr == parent ) { return; }

    if ( m_selfResizer )
    {
        m_selfResizer->Resize( MakeRect( parent->getContentSize() ));
    }

    for ( const auto& resizer : m_resizers )
    {
        resizer->Resize( MakeRect( this->getContentSize() ));
    }
}


void Panel::SetClickHandler( const std::string& name, ClickHandler handler )
{
    auto clickable = dynamic_cast< Clickable* >( this->GetDescendant( name ));
    if ( ! clickable )
    {
        CARAMEL_ALERT( "Widget \"{0}\" is not clickable", name );
        return;
    }

    clickable->SetClickHandler( std::move( handler ));
}


///////////////////////////////////////////////////////////////////////////////
//
// Panel Builder
//

PanelBuilder::PanelBuilder( const std::string& layoutPath, Bool isRoot )
    : m_layoutPath( layoutPath )
    , m_panel( nullptr )
{
    this->LoadJsonRoot();

    m_panel = new Panel;
    m_panel->autorelease();
    m_panel->m_layoutJson = m_layoutJson;

    Path path( layoutPath );
    m_panel->setName( path.Stem().ToString().c_str() );

    if ( isRoot )
    {
        // Read the properties of the panel itself 
        WidgetProperties props;
        props.Parse( m_layoutJson );
        m_panel->m_selfResizer = std::make_shared< WidgetResizer >( m_panel, props );
    }

    this->BuildWidgets();   
}


PanelBuilder::PanelBuilder( const JsonValue& layoutJson )
    : m_layoutJson( layoutJson )
    , m_panel( nullptr )
{
    m_panel = new Panel;
    m_panel->autorelease();
    m_panel->m_layoutJson = m_layoutJson;

    std::string name;
    m_layoutJson.GetString( "name", name );
    m_panel->setName( name.c_str() );

    this->BuildWidgets();   
}


void PanelBuilder::LoadJsonRoot()
{
    auto fileUtils = FileUtils::getInstance();

    if ( ! fileUtils->isFileExist( m_layoutPath ))
    {
        CARAMEL_THROW( "Panel \"{0}\" : layout file not found", m_layoutPath );
    }

    std::string layoutContent = fileUtils->getStringFromFile( m_layoutPath );

    Macaron::RapidJson::JsonReader reader;
    if ( ! reader.Parse( layoutContent, m_layoutJson ))
    {
        CARAMEL_THROW( "Panel \"{0}\" : layout parse failed :\n{1}",
                       m_layoutPath, reader.GetErrorMessage() );
    }

    m_layoutJson.SetTag( "Panel" + m_layoutPath );
}


void PanelBuilder::BuildWidgets()
{
    JsonArray jwidgets;
    if ( ! m_layoutJson.GetArray( "widgets", jwidgets ))
    {
        CARAMEL_TRACE_WARN( "Panel layout \"{0}\" has no \"widgets\" attribute", m_layoutPath );
        return;
    }

    for ( Uint i = 0; i < jwidgets.Size(); ++ i )
    {
        const JsonValue& jwig = jwidgets[i];
        WidgetBuilder builder( jwidgets[i], Format( "{0}[{1}]", jwig.GetTag(), i ));

        ui::Widget* widget = builder.GetWidget();

        // In some case, building a widget failed, but application can continue to run.
        if ( widget )
        {
            m_panel->addChild( widget );

            Panel* subPanel = dynamic_cast< Panel* >( widget );
            if ( subPanel )
            {
                m_panel->m_resizers.push_back(
                    std::make_shared< PanelResizer >( subPanel, builder.GetProperties() ));
            }
            else
            {
                m_panel->m_resizers.push_back(
                    std::make_shared< WidgetResizer >( widget, builder.GetProperties() ));
            }
        }
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// Widget Builder
//

WidgetBuilder::WidgetBuilder( const JsonValue& json, const std::string& path )
    : m_json( json )
    , m_path( path )
    , m_widget( nullptr )
{
    this->ReadNameAndType();
    this->BuildWidgetByType();
}


void WidgetBuilder::ReadNameAndType()
{
    m_name = m_json.GetString( "name" );
    if ( m_name )
    {
        m_path += Format( "\"{0}\"", m_name.get() );
    }

    if ( ! m_json.GetString( "type", m_type ))
    {
        CARAMEL_THROW( "Widget \"{0}\" has no \"type\" attribute", m_path );
    }

    // After read name and type, update JsonValue's tag to make clearer tracing message.
    m_json.SetTag( m_type + " " + m_path );
}


enum WidgetType
{
    WT_IMAGE_VIEW,
    WT_TEXT,
    WT_TEXT_BMFONT,
    WT_LABEL_BUTTON,
    WT_SIMPLE_BUTTON,
    WT_PANEL,
};


void WidgetBuilder::BuildWidgetByType()
{
    static const auto uiTypes = MakeLookupTable
        ( WT_IMAGE_VIEW,    "ImageView", "Image" )
        ( WT_TEXT,          "Text", "Label" )
        ( WT_TEXT_BMFONT,   "TextBMFont", "LabelFont" )
        ( WT_LABEL_BUTTON,  "LabelButton" )
        ( WT_SIMPLE_BUTTON, "SimpleButton", "Button" )
        ( WT_PANEL,         "Panel" );

    WidgetType type;
    if ( ! uiTypes.FindValueByName( m_type, type ))
    {
        CARAMEL_THROW( "Widget \"{0}\" has invalid type: {1}", m_path, m_type );
    }

    switch ( type )
    {
    case WT_IMAGE_VIEW:
        this->BuildImageView();
        break;

    case WT_TEXT:
        this->BuildText();
        break;

    case WT_TEXT_BMFONT:
        this->BuildTextBMFont();
        break;

    case WT_LABEL_BUTTON:
        this->BuildLabelButton();
        break;

    case WT_SIMPLE_BUTTON:
        this->BuildSimpleButton();
        break;

    case WT_PANEL:
        this->BuildPanel();
        break;

    default:
        CARAMEL_NOT_REACHED();
    }
}


void WidgetBuilder::FillWidgetProperties( ui::Widget* widget )
{
    if ( m_name )
    {
        widget->setName( m_name.get().c_str() );
    }

    widget->setVisible( m_props.visible );
    widget->setLocalZOrder( m_props.zOrder );
}


void WidgetBuilder::BuildImageView()
{
    auto image = ui::ImageView::create();

    std::string imagePath;
    if ( m_json.GetString( "imagePath", imagePath ))
    {
        if ( ! FileUtils::getInstance()->isFileExist( imagePath ))
        {
            CARAMEL_ALERT( "Image \"{0}\" - imagePath \"{1}\" not found",
                           m_path, imagePath );
            return;
        }

        image->loadTexture( imagePath );
    }

    m_props.Parse( m_json );

    this->FillWidgetProperties( image );

    // Assign to m_widget only when built successfully.
    m_widget = image;
}


void WidgetBuilder::BuildText()
{
    auto text = ui::Text::create();

    std::string textData;
    if ( m_json.GetString( "text", textData ))
    {
        text->setString( textData );
    }

    Int fontSize = text->getFontSize();
    if ( m_json.GetInt( "fontSize", fontSize ))
    {
        text->setFontSize( fontSize );
    }

    m_props.Parse( m_json );
    this->FillWidgetProperties( text );

    // Assign to m_widget only when built successfully.
    m_widget = text;
}


void WidgetBuilder::BuildTextBMFont()
{
    auto text = ui::TextBMFont::create();

    std::string fontPath;
    if ( m_json.GetString( "fontPath", fontPath ))
    {
        if ( ! FileUtils::getInstance()->isFileExist( fontPath ))
        {
            CARAMEL_ALERT( "BMFont \"{0}\" - fontPath \"{1}\" not found",
                           m_path, fontPath );
            return;
        }

        text->setFntFile( fontPath );
    }

    std::string textData;
    if ( m_json.GetString( "text", textData ))
    {
        text->setString( textData );
    }

    m_props.Parse( m_json );
    this->FillWidgetProperties( text );

    // Assign to m_widget only when built successfully.
    m_widget = text;
}


void WidgetBuilder::BuildLabelButton()
{
    auto button = LabelButton::Create();

    std::string textData;
    if ( m_json.GetString( "text", textData ))
    {
        button->setString( textData );
    }

    Int fontSize = button->getFontSize();
    if ( m_json.GetInt( "fontSize", fontSize ))
    {
        button->setFontSize( fontSize );
    }

    m_props.Parse( m_json );
    this->FillWidgetProperties( button );

    // Assign to m_widget only when built successfully.
    m_widget = button;
}


void WidgetBuilder::BuildSimpleButton()
{
    auto button = SimpleButton::Create();

    std::string normalPath;
    if ( m_json.GetString( "normalPath", normalPath ))
    {
        if ( ! FileUtils::getInstance()->isFileExist( normalPath ))
        {
            CARAMEL_ALERT( "Button \"{0}\" - normalPath \"{1}\" not found",
                           m_path, normalPath );
            return;
        }

        button->loadTextureNormal( normalPath );
    }

    m_props.Parse( m_json );
    this->FillWidgetProperties( button );

    // Assign to m_widget only when built successfully.
    m_widget = button;
}


void WidgetBuilder::BuildPanel()
{
    PanelBuilder builder( m_json );
    auto panel = builder.GetPanel();

    m_props.Parse( m_json );
    this->FillWidgetProperties( panel );

    // Assign to m_widget only when built successfully.
    m_widget = panel;
}


///////////////////////////////////////////////////////////////////////////////
//
// Widget Resizer
//

WidgetResizer::WidgetResizer( ui::Widget* widget, const WidgetProperties& props )
    : m_widget( widget )
    , m_props( props )
{
}


void WidgetResizer::Resize( const Rect& area )
{
    const Bool ignoreSize = m_widget->isIgnoreContentAdaptWithSize();

    if ( WP_FLAG_USE_STRETCH_METHOD & m_props.flags )
    {
        if ( ignoreSize )
        {
            this->StretchWithScale( area );
        }
        else
        {
            this->StretchWithSize( area );
        }
    }
    else
    {
        if ( ignoreSize )
        {
            this->ResizeWithScale();
        }
        else
        {
            this->ResizeWithSize();
        }
    }
}


void WidgetResizer::StretchWithScale( const Rect& area )
{
    m_widget->setAnchorPoint( Vec2::ANCHOR_MIDDLE );
    m_widget->setPosition( GetCenter( area ));

    const Size size = m_widget->getContentSize();

    const Float ratioX = area.size.width / size.width;
    const Float ratioY = area.size.height / size.height;

    switch ( m_props.stretchMethod )
    {
    case STRETCH_AUTO:
    {
        m_widget->setScaleX( ratioX );
        m_widget->setScaleY( ratioY );
        return;
    }

    case STRETCH_FIT:
    {
        m_widget->setScale( std::min( ratioX, ratioY ));
        return;
    }

    case STRETCH_FILL:
    {
        m_widget->setScale( std::max( ratioX, ratioY ));
        return;
    }

    case STRETCH_NONE:
    {
        // Keep the current size.
        m_widget->setScale( 1 );
        return;
    }

    default:
        CARAMEL_NOT_REACHED();
    }
}


void WidgetResizer::StretchWithSize( const Rect& area )
{
    m_widget->setAnchorPoint( Vec2::ZERO );
    m_widget->setPosition( area.origin );

    if ( STRETCH_NONE == m_props.stretchMethod )
    {
        // Keep the current size.
    }
    else
    {
        // All other stretch method has the same result.
        m_widget->setContentSize( area.size );
    }
}


void WidgetResizer::ResizeWithScale()
{
    m_widget->setAnchorPoint( m_props.anchor );
    m_widget->setPosition( m_props.position );

    const Size size = m_widget->getContentSize();

    if ( WP_FLAG_USE_WIDTH & m_props.flags )
    {
        const Float ratioX = m_props.size.width / size.width;
        m_widget->setScaleX( ratioX );
    }

    if ( WP_FLAG_USE_HEIGHT & m_props.flags )
    {
        const Float ratioY = m_props.size.height / size.height;
        m_widget->setScaleY( ratioY );
    }
}


void WidgetResizer::ResizeWithSize()
{
    m_widget->setAnchorPoint( Vec2::ZERO );
    m_widget->setPosition( m_props.position );
    m_widget->setContentSize( m_props.size );
}


///////////////////////////////////////////////////////////////////////////////
//
// Panel Resizer
//

PanelResizer::PanelResizer( Panel* panel, const WidgetProperties& props )
    : WidgetResizer( panel, props )
    , m_panel( panel )
{
}


void PanelResizer::Resize( const Rect& area )
{
    this->WidgetResizer::Resize( area );

    for ( const auto& resizer : m_panel->m_resizers )
    {
        resizer->Resize( MakeRect( m_panel->getContentSize() ));
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// Widget Properties
//

void WidgetProperties::Parse( const JsonValue& json )
{
    this->ParseRect( json );

    json.GetBool( "visible", this->visible );
    json.GetInt( "zOrder", this->zOrder );

    json.GetFloat( "x", this->position.x );
    json.GetFloat( "y", this->position.y );
    
    if ( json.GetFloat( "width", this->size.width ))
    {
        flags |= WP_FLAG_USE_WIDTH;
    }

    if ( json.GetFloat( "height", this->size.height ))
    {
        flags |= WP_FLAG_USE_HEIGHT;
    }

    // left > x
    if ( json.GetFloat( "left", this->position.x ))
    {
        this->anchor.x = 0;
    }
}


void WidgetProperties::ParseRect( const JsonValue& json )
{
    std::string rect;
    if ( ! json.GetString( "rect", rect )) { return; }

    static const auto stretchMethods = MakeLookupTable
        ( STRETCH_NONE, "none" )
        ( STRETCH_FIT,  "fit" )
        ( STRETCH_FILL, "fill" )
        ( STRETCH_AUTO, "auto" );

    if ( stretchMethods.FindValueByText( rect, this->stretchMethod ))
    {
        this->flags |= WP_FLAG_USE_STRETCH_METHOD;
    }
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle
