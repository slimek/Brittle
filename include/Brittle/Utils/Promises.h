// Brittle C++ Library - Utils - Promises Header

#ifndef __BRITTLE_UTILS_PROMISES_H
#define __BRITTLE_UTILS_PROMISES_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>
#include <Caramel/Async/AnyEventTask.h>
#include <Caramel/Task/TaskCompletionSource.h>
#include <2d/CCActionInstant.h>


namespace Brittle
{

///////////////////////////////////////////////////////////////////////////////
//
// Any Event Promise
//

class AnyEventPromise : public TaskCompletionSource< AnyEvent >
{
public:

    CallFunc* Runner( AnyEvent event );
    CallFunc* Runner( Int eventId );
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle

#endif // __BRITTLE_UTILS_PROMISES_H
