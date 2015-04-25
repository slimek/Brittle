// Brittle C++ Library - Notes - Listen Header

#ifndef __BRITTLE_NODES_LISTEN_H
#define __BRITTLE_NODES_LISTEN_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>
#include <2d/CCNode.h>


namespace Brittle
{

///////////////////////////////////////////////////////////////////////////////
//
// Listen Charm
//

class ListenCharm
{
public:
    explicit ListenCharm( Node* listenee );
    ~ListenCharm();

    void Apply();

    
    /// Add Listeners ///

    template< typename Function, typename Target >
    ListenCharm& TouchBegan( const Function& func, const Target& target );


private:

    Node* m_listenee { nullptr };
    Bool  m_applied { false };

    typedef std::function< Bool( Touch*, Event* ) > TouchBeganCallback;
    typedef std::function< void( Touch*, Event* ) > TouchCallback;

    TouchBeganCallback m_touchBegan;
};


inline ListenCharm Listen( Node* listenee )
{
    return ListenCharm( listenee );
}


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

template< typename Function, typename Target >
inline ListenCharm& ListenCharm::TouchBegan( const Function& func, const Target& target )
{
    m_touchBegan = std::bind( func, target, std::placeholders::_1, std::placeholders::_2 );
    return *this;
}


///////////////////////////////////////////////////////////////////////////////

}

#endif // __BRITTLE_NODES_LISTEN_H
