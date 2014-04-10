// Brittle C++ Library - Core Win32 Dependent Implementation

#include "BrittlePch.h"

#include <Brittle/Core/GameApp.h>
#include <Caramel/Windows/DebuggerTraceAdapter.h>


namespace Brittle
{

//
// Contents
//
//   GameApp
//

///////////////////////////////////////////////////////////////////////////////
//
// Game App
//

void GameApp::InitPlatform()
{
    /// Redirect Caramel Trace to Win32 Debugger ///

    auto debugger = new Windows::DebuggerTraceAdapter;
    debugger->BindBuiltinChannels( Trace::LEVEL_DEBUG );
    Trace::Listeners::AddManaged( debugger );


    /// Create GLView with Size and Title ///

    auto director = Director::getInstance();
    CARAMEL_ASSERT( nullptr == director->getOpenGLView() );

    // TODO: Get the Windows title from platform settings.
    auto glview = GLView::create( "Brittle App" );
    director->setOpenGLView( glview );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle
