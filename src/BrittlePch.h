// Brittle C++ Library - Precompiled Header

#ifndef __BRITTLE_BRITTLE_PCH_H
#define __BRITTLE_BRITTLE_PCH_H
#pragma once


///////////////////////////////////////////////////////////////////////////////
//
// Defines
//

#include <Caramel/Setup/PchDefines.h>


///////////////////////////////////////////////////////////////////////////////
//
// Headers
//

// C++ Headers
#include <algorithm>
#include <deque>

// Cocos2d-x Headers
#pragma warning( push )
#pragma warning( disable: 4996 )
#include <cocos2d.h>
#include <ui/CocosGUI.h>
#pragma warning( pop )

// Caramel Headres
#include <Caramel/Setup/PchHeaders.h>
#include <Caramel/String/Format.h>


///////////////////////////////////////////////////////////////////////////////

#endif // __BRITTLE_BRITTLE_PCH_H
