// Brittle C++ Library - Core - Game Application Settings Header

#ifndef __BRITTLE_CORE_GAME_APP_SETTINGS_H
#define __BRITTLE_CORE_GAME_APP_SETTINGS_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>


namespace Brittle
{

///////////////////////////////////////////////////////////////////////////////
//
// Game Application Settings
//

struct GameAppSettings
{
    GameAppSettings()
        : initialSceneId( 0 )
    {}

    Int initialSceneId;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle

#endif // __BRITTLE_CORE_GAME_APP_SETTINGS_H
