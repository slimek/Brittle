// Brittle C++ Library - Nodes - Node Extensions Header

#ifndef __BRITTLE_NODES_NODE_EXTENSIONS_H
#define __BRITTLE_NODES_NODE_EXTENSIONS_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>
#include <2d/CCNode.h>


namespace Brittle
{

///////////////////////////////////////////////////////////////////////////////
//
// Node Extension Functions
//

//
// Translation
//

inline void TranslateX( Node* node, Float xoffset )
{
    node->setPositionX( node->getPositionX() + xoffset );
}


//
// Cooridnations
//

inline Float Left( const Node* node )
{
    return node->getPositionX() - node->getAnchorPointInPoints().x;
}


inline Float Right( const Node* node )
{
    return node->getPositionX()
         + ( node->getContentSize().width - node->getAnchorPointInPoints().x );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle

#endif // __BRITTLE_NODES_NODE_EXTENSIONS_H
