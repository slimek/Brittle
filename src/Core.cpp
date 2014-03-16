// Brittle C++ Library - Core Implementation

#include "BrittlePch.h"

#include <Brittle/Core/GameApp.h>


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
    return true;
}


void GameApp::applicationDidEnterBackground()
{
}


void GameApp::applicationWillEnterForeground()
{
}


Int GameApp::Run( const GameAppSettings& settings )
{
    return EXIT_SUCCESS;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle
