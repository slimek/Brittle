// Brittle C++ Library - Core - Asynchronous Center Header

#ifndef __BRITTLE_CORE_ASYNC_CENTER_H
#define __BRITTLE_CORE_ASYNC_CENTER_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>
#include <Caramel/Object/Singleton.h>
#include <Caramel/Task/TaskPoller.h>


namespace Brittle
{

///////////////////////////////////////////////////////////////////////////////
//
// Asynchronous Center
//

class AsyncCenter : public Singleton< AsyncCenter >
{
public:

    AsyncCenter();

    TaskExecutor& RenderExecutor() { return *m_renderPoller; }

    // Render thread call this function each frame.
    void RenderUpdate();

private:

    std::unique_ptr< TaskPoller > m_renderPoller;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle

#endif // __BRITTLE_CORE_ASYNC_CENTER_H
