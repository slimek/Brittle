// Brittle C++ Library - UI Implementation

#include "BrittlePch.h"

#include "Ui/PanelBuilder.h"
#include "Ui/WidgetBuilder.h"
#include "Ui/WidgetProperties.h"
#include "Ui/WidgetResizer.h"
#include <Brittle/Ui/Panel.h>
#include <Caramel/Data/LookupTable.h>
#include <Caramel/FileSystem/Path.h>
#include <JsonCpp/reader.h>
#include <ui/UIImageView.h>
#include <ui/UIText.h>
#include <ui/UITextBMFont.h>


namespace Brittle
{

//
// Content
//
//   Panel
//   PanelBuilder
//   WidgetBuilder
//   WidgetResizer
//   WidgetProperties
//

///////////////////////////////////////////////////////////////////////////////
//
// Panel
//

Panel* Panel::Create( const std::string& layoutPath )
{
    PanelBuilder builder( layoutPath );
    return builder.GetPanel();
}


ui::Widget* Panel::GetChild( const std::string& name ) const
{
    // TODO: In v3.0 ui::Widget::getChildByName() is non-const ...

    auto widget = const_cast< Panel* >( this )->getChildByName( name.c_str() );
    if ( ! widget )
    {
        CARAMEL_THROW( "Panel %s child %s not found", this->getName(), name );
    }
    return widget;
}


void Panel::setParent( Node* parent )
{
    this->ui::Widget::setParent( parent );

    if ( nullptr == parent ) { return; }

    for ( const auto& resizer : m_resizers )
    {
        resizer->Resize( this );
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// Panel Builder
//

PanelBuilder::PanelBuilder( const std::string& layoutPath )
    : m_layoutPath( layoutPath )
    , m_panel( nullptr )
{
    this->LoadJsonRoot();

    m_panel = new Panel;
    m_panel->autorelease();
    m_panel->m_layoutJson = m_layoutJson;

    Path path( layoutPath );
    m_panel->setName( path.Stem().ToString().c_str() );

    // Read the properties of the panel itself 
    WidgetProperties props;
    props.Parse( m_layoutJson );
    m_panel->m_resizers.push_back( std::make_shared< WidgetResizer >( m_panel, props ));

    this->BuildWidgets();   
}


void PanelBuilder::LoadJsonRoot()
{
    auto fileUtils = FileUtils::getInstance();

    if ( ! fileUtils->isFileExist( m_layoutPath ))
    {
        CARAMEL_THROW( "Panel %s : layout file not found", m_layoutPath );
    }

    std::string layoutContent = fileUtils->getStringFromFile( m_layoutPath );

    Json::Value json;
    Json::Reader reader;
    if ( ! reader.parse( layoutContent, json ))
    {
        CARAMEL_THROW( "Panel %s : layout parse failed :\n%s",
                       m_layoutPath, reader.getFormatedErrorMessages() );
    }

    m_layoutJson = JsonValue( json, "Panel " + m_layoutPath );
}


void PanelBuilder::BuildWidgets()
{
    Json::Value widgets;
    if ( ! m_layoutJson.GetArray( "widgets", widgets ))
    {
        CARAMEL_TRACE_WARN( "Panel layout %s has no \"widgets\" attribute", m_layoutPath );
        return;
    }

    for ( Uint i = 0; i < widgets.size(); ++ i )
    {
        WidgetBuilder builder( widgets[i], Format( "{0}[{1}]", m_layoutPath, i ));

        ui::Widget* widget = builder.GetWidget();

        // In some case, building a widget failed, but application can continue to run.
        if ( widget )
        {
            m_panel->addChild( widget );

            m_panel->m_resizers.push_back(
                std::make_shared< WidgetResizer >( widget, builder.GetProperties() ));
        }
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// Widget Builder
//

WidgetBuilder::WidgetBuilder( const Json::Value& json, const std::string& path )
    : m_json( json, "Widget " + path )
    , m_path( path )
    , m_widget( nullptr )
{
    this->ReadNameAndType();
    this->BuildWidgetByType();
}


void WidgetBuilder::ReadNameAndType()
{
    if ( m_json.GetString( "name", m_name ))
    {
        m_path += Format( "\"{0}\"", m_name.get() );
    }

    if ( ! m_json.GetString( "type", m_type ))
    {
        CARAMEL_THROW( "Widget %s has no \"type\" attribute", m_path );
    }

    // 讀取 name 和 type 之後，更新 JsonValue 的 tag，使錯誤訊息更清楚。
    m_json.SetTag( m_type + " " + m_path );
}


enum WidgetType
{
    WT_IMAGE_VIEW,
    WT_TEXT,
    WT_TEXT_BMFONT,
};


void WidgetBuilder::BuildWidgetByType()
{
    static const auto uiTypes = LookupTable< WidgetType >
        ( WT_IMAGE_VIEW,  "ImageView", "Image" )
        ( WT_TEXT,        "Text", "Label" )
        ( WT_TEXT_BMFONT, "TextBMFont", "LabelFont" );

    WidgetType type;
    if ( ! uiTypes.FindValueByName( m_type, type ))
    {
        CARAMEL_THROW( "Widget %s has invalid type: %s", m_path, m_type );
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

    default:
        CARAMEL_NOT_REACHED();
    }
}


void WidgetBuilder::FillWidgetName( ui::Widget* widget )
{
    if ( m_name )
    {
        widget->setName( m_name.get().c_str() );
    }
}


void WidgetBuilder::BuildImageView()
{
    auto image = ui::ImageView::create();

    std::string imagePath;
    if ( m_json.GetString( "imagePath", imagePath ))
    {
        if ( ! FileUtils::getInstance()->isFileExist( imagePath ))
        {
            CARAMEL_ALERT( "Image %s - imagePath %s not found",
                           m_path, imagePath );
            return;
        }

        image->loadTexture( imagePath );
    }

    m_props.Parse( m_json );

    this->FillWidgetName( image );

    // Assign to m_widget only when built successfully.
    m_widget = image;
}


void WidgetBuilder::BuildText()
{
    auto text = ui::Text::create();

    std::string textData;
    if ( m_json.GetString( "text", textData ))
    {
        text->setText( textData );
    }

    Int fontSize = text->getFontSize();
    if ( m_json.GetInt( "fontSize", fontSize ))
    {
        text->setFontSize( fontSize );
    }

    m_props.Parse( m_json );
    this->FillWidgetName( text );

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
            CARAMEL_ALERT( "BMFont %s - fontPath %s not found",
                           m_path, fontPath );
        }

        text->setFntFile( fontPath );
    }

    std::string textData;
    if ( m_json.GetString( "text", textData ))
    {
        text->setText( textData );
    }

    m_props.Parse( m_json );
    this->FillWidgetName( text );

    // Assign to m_widget only when built successfully.
    m_widget = text;
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


void WidgetResizer::Resize( Node* parent )
{
    if ( WP_FLAG_RECT_IS_SCENE & m_props.flags )
    {
        auto scene = Director::getInstance()->getRunningScene();
        m_widget->setPosition( Point( 0, 0 ));
        m_widget->setContentSize( scene->getContentSize() );
    }
    else
    {
        m_widget->setPosition( m_props.position );
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// Widget Properties
//

void WidgetProperties::Parse( const JsonValue& json )
{
    this->ParseRect( json );

    json.GetFloat( "x", this->position.x );
    json.GetFloat( "y", this->position.y );
}


void WidgetProperties::ParseRect( const JsonValue& json )
{
    std::string rect;
    if ( ! json.GetString( "rect", rect )) { return; }

    static const auto stretchMethods = MakeLookupTable
        ( STRETCH_FIT,     "fit" )
        ( STRETCH_FILL,    "fill" )
        ( STRETCH_STRETCH, "stretch" );

    if ( stretchMethods.FindValueByText( rect, this->stretchMethod ))
    {
        this->flags |= WP_FLAG_USE_STRETCH_METHOD;
    }

    if ( "scene" == rect )
    {
        this->flags |= WP_FLAG_RECT_IS_SCENE;
    }
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle
