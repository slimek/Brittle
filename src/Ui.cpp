// Brittle C++ Library - UI Implementation

#include "BrittlePch.h"

#include "Ui/PanelBuilder.h"
#include <Brittle/Ui/Panel.h>
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
        CARAMEL_THROW( "Panel layout file %s not found", m_layoutPath );
    }

    std::string layoutContent = fileUtils->getStringFromFile( m_layoutPath );

    Json::Reader reader;
    if ( ! reader.parse( layoutContent, m_rootJson ))
    {
        CARAMEL_THROW( "Panel layout file %s parse failed :\n%s",
                       m_layoutPath, reader.getFormatedErrorMessages() );
    }
}


void PanelBuilder::BuildWidgets()
{
    
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle
