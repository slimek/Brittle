// Brittle C++ Library - Core - Asynchronous Header

#ifndef __BRITTLE_CORE_ASYNC_H
#define __BRITTLE_CORE_ASYNC_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>
#include <Caramel/Task/TaskExecutor.h>


namespace Brittle
{

///////////////////////////////////////////////////////////////////////////////
//
// Asynchronous
//

class Async
{
public:

    /// Executors ///

    static TaskExecutor& RenderExecutor();


private:

    friend class GameApp;

    /// Functions only called by GameApp ///

    // Render thread call this function to poll RenderExecutor.
    static void RenderUpdate();

};


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle

#endif // __BRITTLE_CORE_ASYNC_H
