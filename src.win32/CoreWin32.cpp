// Brittle C++ Library - Core Win32 Dependent Implementation

#include "BrittlePch.h"

#include <Brittle/Core/SimpleApp.h>
#include <Caramel/Windows/DebuggerTraceAdapter.h>
#include <base/ObjectFactory.h>


namespace Brittle
{

//
// Contents
//
//   SimpleApp
//

///////////////////////////////////////////////////////////////////////////////
//
// Simple Application
//

void SimpleApp::InitPlatform()
{
    /// Redirect Caramel Trace to Win32 Debugger ///

    auto debugger = new Windows::DebuggerTraceAdapter;
    debugger->BindBuiltinChannels( Trace::LEVEL_DEBUG );
    Trace::Listeners::AddManaged( debugger );


    /// Create GLView with Size and Title ///

    const DesktopSettings& ds = m_settings.desktop;

    auto glview = GLViewImpl::createWithRect(
        ds.frameTitle, Rect( 0, 0, ds.frameWidth, ds.frameHeight ));

    auto director = Director::getInstance();
    CARAMEL_ASSERT( nullptr == director->getOpenGLView() );

    director->setOpenGLView( glview );


    //
    // Specify Assets path in Win32
    // - 1. Relateive path from working directory to assets.
    //   2. Add an additional assets.win32 .
    //

    if ( ds.assetsPath.empty() )
    {
        CARAMEL_THROW( "Assets path not set" );
    }

    auto fileUtils = FileUtils::getInstance();

    fileUtils->addSearchPath( ds.assetsPath );
    fileUtils->addSearchPath( ds.assetsPath + ".win32" );
}


void SimpleApp::ExitPlatform()
{
    ObjectFactory::destroyInstance();
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle
