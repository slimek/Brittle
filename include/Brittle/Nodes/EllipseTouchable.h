// Brittle C++ Library - Nodes - Ellipse Touchable Header

#ifndef __BRITTLE_NODES_ELLIPSE_TOUCHABLE_H
#define __BRITTLE_NODES_ELLIPSE_TOUCHABLE_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>
#include <2d/CCNode.h>
#include <functional>


namespace Brittle
{

///////////////////////////////////////////////////////////////////////////////
//
// Ellipse Touchable
//

class EllipseTouchable : public Node
{
public:

    // Create a node with autorelease.
    static EllipseTouchable* Create();

    Bool IsClicked() const { return m_clicked; }

    std::function< Bool() > GetClickCondition() const;

    void Clear();


    /// Overrides ///

    virtual void setParent( Node* parent ) override;

private:

    // Seal the base function.
    using Node::create;


    /// Touch Events ///

    Bool OnTouchBegan( Touch* touch, Event* event );
    void OnTouchEnded( Touch* touch, Event* event );


    /// Members ///

    // Squares of radius on each axis
    Float m_radiusX2 { 0 };
    Float m_radiusY2 { 0 };

    Bool m_clicked { false };
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle

#endif // __BRITTLE_NODES_ELLIPSE_TOUCHABLE_H
