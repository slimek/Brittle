// Brittle C++ Library - Core - Game Application Header

#ifndef __BRITTLE_CORE_GAME_APP_H
#define __BRITTLE_CORE_GAME_APP_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>
#include <Brittle/Core/GameAppSettings.h>


namespace Brittle
{

///////////////////////////////////////////////////////////////////////////////
//
// Game Application
//

class GameApp : public Application
{
public:

    /// Accessors ///

    static GameApp* Instance();

    
    /// Run / Launch ///

    #if defined( CARAMEL_SYSTEM_IS_WINDOWS )

    Int Run( const GameAppSettings& s );

    #endif

    #if defined( CARAMEL_SYSTEM_IS_IOS ) || defined( CARAMEL_SYSTEM_IS_ANDROID )

    Bool Launch( const GameAppSettings& s );

    #endif


    /// Application Protocol Events ///

    Bool applicationDidFinishLaunching() final override;
    void applicationDidEnterBackground() final override;
    void applicationWillEnterForeground() final override;


    /// Scene Management ///

    void ReplaceScene( Int sceneId );


private:

    /// Application Events ///

    virtual void OnLaunch() {}
    virtual void OnEnterBackground() {}
    virtual void OnEnterForeground() {}


    /// Scene Management ///

    virtual GameScene* CreateScene( Int sceneId ) = 0;


    /// Platform Dependent ///

    void InitPlatform();
    void ExitPlatform();


    /// Data Members ///

    GameAppSettings m_settings;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle

#endif // __BRITTLE_CORE_GAME_APP_H
