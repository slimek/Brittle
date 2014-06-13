// Brittle C++ Library - Core - Frame Clock Header

#ifndef __BRITTLE_CORE_FRAME_CLOCK_H
#define __BRITTLE_CORE_FRAME_CLOCK_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>
#include <Caramel/Chrono/SecondClock.h>


namespace Brittle
{

///////////////////////////////////////////////////////////////////////////////
//
// Frame Clock
// - A second clock which advances at the begin of each frame.
//   It keeps the same time in a frame.
//

class FrameTime;

class FrameClock
{
public:
    
    typedef FrameTime TimePoint;
    typedef Seconds Duration;

    static FrameTime Now();

private:

    friend class SimpleApp;
    static void Advance( Float delta );

    static Seconds m_sinceEpoch;
};


///////////////////////////////////////////////////////////////////////////////
//
// Frame Time
// - The time point type of FrameClock.
//

class FrameTime
    : public boost::chrono::time_point<
        FrameClock, boost::chrono::duration< Double, boost::ratio< 1 > >
      >
{
    typedef boost::chrono::time_point<
        FrameClock, boost::chrono::duration< Double, boost::ratio< 1 > >
    > Inherited;

public:
    explicit FrameTime( const Seconds& sinceEpoch );
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle

#endif // __BRITTLE_CORE_FRAME_CLOCK_H
