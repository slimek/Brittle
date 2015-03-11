// Brittle C++ Library - Nodes - Scrolling Node Header

#ifndef __BRITTLE_NODES_SCROLLING_NODE_H
#define __BRITTLE_NODES_SCROLLING_NODE_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>
#include <2d/CCClippingRectangleNode.h>


namespace Brittle
{

///////////////////////////////////////////////////////////////////////////////
//
// Horizontal Scrolling
// - A node which automatically scrolls its content, horizontally.
//

class HorizontalScrolling : public ClippingRectangleNode
{
public:

    // Create a node with autorelease
    // - You may add 1 or 2 textures.
    static HorizontalScrolling* Create( const std::vector< Texture2D* >& textures );
    static HorizontalScrolling* Create( const std::vector< std::string >& filePaths );

    /// Start and stop actions ///

    // If the velocity > 0, the node is scrolling to right,
    // i.e, the internal nodes move from left to right.
    void Start( Float velocity );
    
    void Stop();


private:

    void Init( const std::vector< Texture2D* >& textures );

    void update( Float delta ) override;

    void LocateLeft();
    void LocateRight();

    Float m_velocity { 0.0f };
    Bool m_running { false };

    Node* m_left { nullptr };
    Node* m_right { nullptr };
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle

#endif // __BRITTLE_NODES_SCROLLING_NODE_H
