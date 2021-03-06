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
    void applicationWillTerminate() final override;  // Desktop only


    /// Scheduling ///

    // Schedule per frame update
    // - This function would be called by CCScheduler
    void update( Float delta );


    /// Scene Management ///

    void ReplaceScene( Int sceneId );


    /// Properties ///

    Size GetDesignSize() const;


protected:

    //
    // App Descriptor
    // - No default values. You must desinate theme.
    //
    struct AppDesc
    {
        // Design resolution.
        Float designWidth;
        Float designHeight;

        Int initialSceneId;
    };

    explicit SimpleApp( const AppDesc& desc );


private:


    /// Application Events ///

    virtual void OnLaunch() {}
    virtual void OnEnterBackground() {}
    virtual void OnEnterForeground() {}
    virtual void OnTerminate() {}  // Desktop only


    /// Scene Management ///

    // Returns a SimpleScene according to the ID.
    // - This scene can be created by SimpleScene::Create< T >() or similar functions.
    //   It should have been autoreleased.
    virtual SimpleScene* CreateScene( Int sceneId ) = 0;


    /// Platform Dependent ///

    void InitPlatform();
    void ExitPlatform();

    
    /// Data Members ///

    // Descriptor is the same on all platforms/configurations.
    AppDesc m_desc;

    // Settings may differ across platforms/configurations.
    AppSettings m_settings;
};


} // namespace Brittle

///////////////////////////////////////////////////////////////////////////////
//
// App Exporting Functions
// - The apps should provide these functions on each platform, respectively.
//

//
// Android Initialize
// - The apps MUST create a SimpleApp derived class, and fill the settings.
//
void NativeInit( Brittle::SimpleApp*& app, Brittle::AppSettings& settings );


///////////////////////////////////////////////////////////////////////////////

#endif // __BRITTLE_CORE_SIMPLE_APP_H
