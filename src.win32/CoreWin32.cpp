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

    const DesktopSettings& ds = m_settings.desktop;

    auto glview = GLView::create( ds.frameTitle );
    glview->setFrameSize( ds.frameWidth, ds.frameHeight );

    auto director = Director::getInstance();
    CARAMEL_ASSERT( nullptr == director->getOpenGLView() );

    director->setOpenGLView( glview );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle
