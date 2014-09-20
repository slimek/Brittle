// Brittle C++ Library - Setup - Basic Defines Header

// This header is included by all Brittle public headers at the first.

#ifndef __BRITTLE_SETUP_BRITTLE_DEFS_H
#define __BRITTLE_SETUP_BRITTLE_DEFS_H
#pragma

#include <Caramel/Setup/CaramelDefs.h>
#include <cocos2d.h>


namespace Brittle
{

using namespace cocos2d;
using namespace Caramel;


//
// Forward Declarations
//

// Core Components
class SimpleApp;
class SimpleScene;

// Application Settings
struct AppSettings;
struct DesktopSettings;


} // namespace Brittle


//
// Compiler / System Setup
//

#if defined( CARAMEL_SYSTEM_IS_WINDOWS )

#define BRITTLE_SYSTEM_IS_DESKTOP

#elif defined( CARAMEL_SYSTEM_IS_IOS ) || defined( CARAMEL_SYSTEM_IS_ANDROID )

#define BRITTLE_SYSTEM_IS_MOBILE

#else
#error System not determined
#endif

#endif // __BRITTLE_SETUP_BRITTLE_DEFS_H
