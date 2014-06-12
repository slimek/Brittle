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
// Typedefs
//

typedef Caramel::Bool  Bool;
typedef Caramel::Float Float;


//
// Forward Declarations
//

class SimpleApp;
class SimpleScene;


} // namespace Brittle


#endif // __BRITTLE_SETUP_BRITTLE_DEFS_H
