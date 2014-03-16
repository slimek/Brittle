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

    
    /// Run / Launch ///

    #if defined( CARAMEL_SYSTEM_IS_WINDOWS )

    Int Run( const GameAppSettings& s );

    #endif

    #if defined( CARAMEL_SYSTEM_IS_IOS ) || defined( CARAMEL_SYSTEM_IS_ANDROID )

    Bool Launch( const GameAppSettings& s );

    #endif


    /// Application Protocol Events ///

    Bool applicationDidFinishLaunching() override;
    void applicationDidEnterBackground() override;
    void applicationWillEnterForeground() override;

};


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle

#endif // __BRITTLE_CORE_GAME_APP_H
