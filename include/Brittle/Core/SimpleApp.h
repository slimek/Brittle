// Brittle C++ Library - Core - Simple Application Header

#ifndef __BRITTLE_CORE_SIMPLE_APP_H
#define __BRITTLE_CORE_SIMPLE_APP_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>
#include <Brittle/Core/AppSettings.h>


namespace Brittle
{

///////////////////////////////////////////////////////////////////////////////
//
// Simple Application
//

class SimpleApp : public Application
{
public:

    /// Accessors ///

    static SimpleApp* Instance();

    
    /// Run / Launch ///

    #if defined( BRITTLE_SYSTEM_IS_DESKTOP )

    Int Run( const AppSettings& s );

    #endif

    #if defined( BRITTLE_SYSTEM_IS_MOBILE )

    void Launch( const AppSettings& s );

    #endif


    /// Application Protocol Events ///

    Bool applicationDidFinishLaunching() final override;
    void applicationDidEnterBackground() final override;
    void applicationWillEnterForeground() final override;


    /// Scheduling ///

    // Schedule per frame update
    // - This function would be called by CCScheduler
    void update( Float delta );


    /// Scene Management ///

    void ReplaceScene( Int sceneId );


private:

    /// Application Events ///

    virtual void OnLaunch() {}
    virtual void OnEnterBackground() {}
    virtual void OnEnterForeground() {}


    /// Scene Management ///

    // Returns a SimpleScene according to the ID.
    // - This scene can be created by SimpleScene::Create< T >() or similar functions.
    //   It should have been autoreleased.
    virtual SimpleScene* CreateScene( Int sceneId ) = 0;


    /// Platform Dependent ///

    void InitPlatform();
    void ExitPlatform();

    
    /// Data Members ///

    AppSettings m_settings;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle

#endif // __BRITTLE_CORE_SIMPLE_APP_H
