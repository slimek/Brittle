// Brittle C++ Library - UI Implementation

#include "BrittlePch.h"

#include "Ui/PanelBuilder.h"
#include <Brittle/Ui/Panel.h>
#include <Brittle/Utils/JsonUtils.h>
#include <JsonCpp/reader.h>


namespace Brittle
{

//
// Content
//
//   Panel
//   PanelBuilder
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


///////////////////////////////////////////////////////////////////////////////
//
// Panel Builder
//

PanelBuilder::PanelBuilder( const std::string& layoutPath )
    : m_layoutPath( layoutPath )
{
    this->LoadJsonRoot();

    m_panel = new Panel;
    m_panel->autorelease();
 
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
        CARAMEL_TRACE_WARN( "Panel layout %s has no \"widgets\" value", m_layoutPath );
        return;
    }

    for ( const auto& widget : widgets )
    {
        ; // TODO: Build each Widget.
    }
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle
