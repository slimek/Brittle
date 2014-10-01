// Brittle C++ Library - Nodes Implementation

#include "BrittlePch.h"

#include <Brittle/Nodes/EllipseTouchable.h>
#include <Brittle/Layout/Locate.h>


namespace Brittle
{

//
// [Contents]
//
//   EllipseTouchable
//

///////////////////////////////////////////////////////////////////////////////
//
// Ellipse Touchable
//

EllipseTouchable* EllipseTouchable::Create()
{
    auto node = new EllipseTouchable;
    if ( node->init() )
    {
        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches( true );
        listener->onTouchBegan = CC_CALLBACK_2( EllipseTouchable::OnTouchBegan, node );
        listener->onTouchEnded = CC_CALLBACK_2( EllipseTouchable::OnTouchEnded, node );
        node->getEventDispatcher()->addEventListenerWithSceneGraphPriority( listener, node );

        node->autorelease();
    }
    return node;
}


std::function< Bool() > EllipseTouchable::GetClickCondition() const
{
    return [=] { return this->m_clicked; };
}


void EllipseTouchable::Clear()
{
    m_clicked = false;
}


//
// Overrides
//

void EllipseTouchable::setParent( Node* parent )
{
    this->Node::setParent( parent );

    Locate( this ).Center();

    const auto size = parent->getContentSize();
    m_radiusX2 = ( size.width * size.width ) / 4;
    m_radiusY2 = ( size.height * size.height ) / 4;
}


//
// Touch Events
//

Bool EllipseTouchable::OnTouchBegan( Touch* touch, Event* event )
{
    const auto point = this->convertTouchToNodeSpaceAR( touch );
    
    const auto distX2 = point.x * point.x;
    const auto distY2 = point.y * point.y;

    return ( distX2 / m_radiusX2 + distY2 / m_radiusY2 ) <= 1.0f;
}


void EllipseTouchable::OnTouchEnded( Touch* touch, Event* event )
{
    m_clicked = true;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle
