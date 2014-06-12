// Brittle C++ Library - Core - Application Settings Header

#ifndef __BRITTLE_CORE_APP_SETTINGS_H
#define __BRITTLE_CORE_APP_SETTINGS_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>


namespace Brittle
{

///////////////////////////////////////////////////////////////////////////////
//
// Desktop Settings
//

struct DesktopSettings
{
    DesktopSettings()
        : frameWidth( 800 )
        , frameHeight( 600 )
    {}

    Float frameWidth;
    Float frameHeight;
    std::string frameTitle;
    std::string assetsPath;
};


///////////////////////////////////////////////////////////////////////////////
//
// Application Settings - Integrated
//

struct AppSettings
{
    AppSettings()
        : initialSceneId( 0 )
    {}

    Int initialSceneId;

    DesktopSettings desktop;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle

#endif // __BRITTLE_CORE_APP_SETTINGS_H
