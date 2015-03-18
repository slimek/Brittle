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
    // Properties of the frame window
    Float frameWidth { 800 };
    Float frameHeight { 600 };
    std::string frameTitle;

    std::string assetsPath;
};


///////////////////////////////////////////////////////////////////////////////
//
// Application Settings
// - For the same app, each platform has its own setting.
//

struct AppSettings
{
    Int initialSceneId { 0 };
    
    DesktopSettings desktop;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle

#endif // __BRITTLE_CORE_APP_SETTINGS_H
