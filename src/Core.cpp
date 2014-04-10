// Brittle C++ Library - Core Implementation

#include "BrittlePch.h"

#include <Brittle/Core/GameApp.h>
#include <Caramel/Error/CatchException.h>


namespace Brittle
{

//
// [Contents]
//
//   GameApp
//

///////////////////////////////////////////////////////////////////////////////
//
// Game Application
//

Bool GameApp::applicationDidFinishLaunching()
{
    CARAMEL_TRACE_INFO( "Application Did Finish Launching" );

    this->OnLaunch();
    return true;
}


void GameApp::applicationDidEnterBackground()
{
    this->OnEnterBackground();
}


void GameApp::applicationWillEnterForeground()
{
    this->OnEnterForeground();
}


//
// Entry from Platform Dependent Scope
//

Int GameApp::Run( const GameAppSettings& settings )
{
    m_settings = settings;

    this->InitPlatform();

    auto xc = CatchException( [=] ()-> Int { return this->run(); } );
    if ( xc )
    {
        CARAMEL_ALERT( "Application::run() throws:\n%s", xc.TracingMessage() );
        return EXIT_FAILURE;
    }

    return xc.Result();
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle
