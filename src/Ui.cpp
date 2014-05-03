// Brittle C++ Library - UI Implementation

#include "BrittlePch.h"

#include "Ui/PanelBuilder.h"
#include "Ui/WidgetAttributes.h"
#include "Ui/WidgetBuilder.h"
#include <Brittle/Ui/Panel.h>
#include <Brittle/Utils/JsonUtils.h>
#include <Caramel/Data/LookupTable.h>
#include <Caramel/FileSystem/Path.h>
#include <JsonCpp/reader.h>
#include <ui/UIImageView.h>


namespace Brittle
{

//
// Content
//
//   Panel
//   PanelBuilder
//   WidgetBuilder
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

    Path path( layoutPath );
    m_panel->setName( path.Stem().ToString().c_str() );
 
    this->BuildWidgets();   
}


void PanelBuilder::LoadJsonRoot()
{
    auto fileUtils = FileUtils::getInstance();

    if ( ! fileUtils->isFileExist( m_layoutPath ))
    {
        CARAMEL_THROW( "Panel layout %s file not found", m_layoutPath );
    }

    std::string layoutContent = fileUtils->getStringFromFile( m_layoutPath );

    Json::Reader reader;
    if ( ! reader.parse( layoutContent, m_rootJson ))
    {
        CARAMEL_THROW( "Panel layout %s parse failed :\n%s",
                       m_layoutPath, reader.getFormatedErrorMessages() );
    }
}


void PanelBuilder::BuildWidgets()
{
    Bool b1 = m_rootJson.isMember( "widgets" );

    Json::Value widgets;
    if ( ! QueryArray( m_rootJson, "widgets", widgets ))
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
        }
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// Widget Builder
//

WidgetBuilder::WidgetBuilder( const Json::Value& json, const std::string& path )
    : m_json( json )
    , m_path( path )
    , m_widget( nullptr )
{
    this->ReadNameAndType();
    this->BuildWidgetByType();
}


void WidgetBuilder::ReadNameAndType()
{
    std::string name;
    if ( QueryString( m_json, "name", name ))
    {
        m_path += Format( "\"{0}\"", name );
    }

    if ( ! QueryString( m_json, "type", m_type ))
    {
        CARAMEL_THROW( "Widget %s has no \"type\" attribute", m_path );
    }
}


enum WidgetType
{
    WT_IMAGE_VIEW,
};


void WidgetBuilder::BuildWidgetByType()
{
    static const auto uiTypes = LookupTable< WidgetType >
        ( WT_IMAGE_VIEW, "Image", "ImageView" );

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

    default:
        CARAMEL_NOT_REACHED();
    }
}


void WidgetBuilder::ReadWidgetAttributes( WidgetAttributes& attrs )
{
    QueryString( m_json, "name", attrs.name );
    
    QueryFloat( m_json, "x", attrs.position.x );
    QueryFloat( m_json, "y", attrs.position.y );
}



void WidgetBuilder::BuildImageView()
{
    WidgetAttributes attrs;
    this->ReadWidgetAttributes( attrs );

    auto image = ui::ImageView::create();

    image->setName( attrs.name.c_str() );
    image->setPosition( attrs.position );

    std::string imagePath;
    if ( QueryString( m_json, "imagePath", imagePath ))
    {
        if ( ! FileUtils::getInstance()->isFileExist( imagePath ))
        {
            CARAMEL_ALERT( "Image %s - imagePath %s not found",
                           m_path, imagePath );
            return;
        }

        image->loadTexture( imagePath );
    }

    m_widget = image;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle
