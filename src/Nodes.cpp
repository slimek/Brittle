// Brittle C++ Library - Nodes Implementation

#include "BrittlePch.h"

#include <Brittle/Nodes/EllipseTouchable.h>
#include <Brittle/Nodes/HorizontalScrolling.h>
#include <Brittle/Nodes/NodeExtensions.h>
#include <Brittle/Layout/Locate.h>
#include <Brittle/Utils/Geometry.h>
#include <Caramel/Memory/UniquePtrUtils.h>


namespace Brittle
{

//
// [Contents]
//
//   EllipseTouchable
//   HorizontalScrolling
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
    else
    {
        CC_SAFE_DELETE( node );
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
//
// Horizontal Scrolling
//

HorizontalScrolling* HorizontalScrolling::Create( const std::vector< Texture2D* >& textures )
{
    if ( textures.empty() )
    {
        CARAMEL_THROW( "No texture given" );
    }

    auto node = MakeUnique< HorizontalScrolling >();
    CARAMEL_CHECK( node->init() );

    node->Init( textures );
    node->autorelease();

    return node.release();
}


HorizontalScrolling* HorizontalScrolling::Create( const std::vector< std::string >& filePaths )
{
    auto texCache = Director::getInstance()->getTextureCache();

    std::vector< Texture2D* > textures;
    textures.reserve( filePaths.size() );
    for ( const auto& filePath : filePaths )
    {
        auto tex = texCache->addImage( filePath );
        if ( ! tex )
        {
            CARAMEL_ALERT( "Texture file \"{0}\" not found", filePath );
            continue;
        }
        textures.push_back( tex );
    }

    return Create( textures );
}


void HorizontalScrolling::Init( const std::vector< Texture2D* >& textures )
{
    CARAMEL_ASSERT( ! textures.empty() );
    
    m_left = Sprite::createWithTexture( textures[0] );

    if ( textures.size() > 1 )
    {
        m_right = Sprite::createWithTexture( textures[1] );
        if ( m_left->getContentSize() != m_right->getContentSize() )
        {
            CARAMEL_ALERT( "Content size of two textures are not the same: \"{0}\" and \"{1}\"",
                           textures[0]->getName(), textures[1]->getName() );
        }
    }
    else
    {
        m_right = Sprite::createWithTexture( textures[0] );
    }

    const auto size = m_left->getContentSize();

    this->setContentSize( size );
    this->setClippingRegion( MakeRect( size ));

    this->addChild( m_left );
    Locate( m_left ).Center();

    this->addChild( m_right );
    Locate( m_right ).CenterY();

    this->LocateRight();

    this->scheduleUpdate();
}


void HorizontalScrolling::Start( Float velocity )
{
    m_velocity = velocity;
    m_running = true;

    if ( m_velocity > 0 && Left( m_right ) >= this->getContentSize().width )
    {
        std::swap( m_left, m_right );
        this->LocateLeft();
    }
}


void HorizontalScrolling::Stop()
{
    m_running = false;
}


void HorizontalScrolling::LocateLeft()
{
    CARAMEL_ASSERT( m_velocity > 0 );

    m_left->setPositionX(
        m_right->getPositionX() - m_left->getContentSize().width );
}


void HorizontalScrolling::LocateRight()
{
    CARAMEL_ASSERT( m_velocity <= 0 );

    m_right->setPositionX(
        m_left->getPositionX() + m_left->getContentSize().width );
}


void HorizontalScrolling::update( Float delta )
{
    if ( ! m_running ) { return; }

    if ( m_velocity > 0 )
    {
        // Scrolling to Right : Move nodes to right.

        TranslateX( m_right, delta * m_velocity );
        if ( Left( m_right ) > this->getContentSize().width )
        {
            std::swap( m_right, m_left );
        }

        this->LocateLeft();
    }
    else
    {
        // Scrolling to Left : Move nodes to left.

        TranslateX( m_left, delta * m_velocity );
        if ( Right( m_left ) < 0.0f )
        {
            std::swap( m_right, m_left );
        }

        this->LocateRight();
    }
}


#if 0

    const auto size = m_leader->getContentSize();

    this->setContentSize( size );
    this->setClippingRegion( MakeRect( size ));

    this->addChild( m_leader );
    Locate( m_leader ).Center();

    this->addChild( m_follower );
    m_follower->setPosition( m_leader->getPosition() - m_leader->getContentSize() );
    this->LocateFollower();

    return true;
}


void ScrollingNode::Start( Float velocity )
{
    m_velocity = velocity;
    m_running = true;

    const Bool positive = ( m_velocity > 0 );

    switch ( m_orientation )
    {
    case ORIENTATION_HORIZONTAL:
    {
        if ( positive != ( m_leader->getPositionX() > m_follower->getPositionX() ))
        {
            std::swap( m_leader, m_follower );
        }
        break;
    }    

    case ORIENTATION_VERTICAL:
    {
        if ( positive != ( m_leader->getPositionY() > m_follower->getPositionY() ))
        {
            std::swap( m_leader, m_follower );
        }
        break;
    }

    default:
        CARAMEL_NOT_REACHED();
    }


    this->LocateFollower();
}


void ScrollingNode::update( Float delta )
{
    if ( ! m_running ) { return; }

    switch ( m_orientation )
    {
    case ORIENTATION_HORIZONTAL:
    {
        m_leader->setPositionX( m_leader->getPositionX() + delta * m_velocity );
        if ( m_velocity > 0 && m_leader->getPositionX() > this->getContentSize().width )
        {
            std::swap( m_leader, m_follower );
        }
        else if ( m_leader->getPositionX() < 0 )
        {
            std::swap( m_leader, m_follower );
        }
        break;
    }

    case ORIENTATION_VERTICAL:

    default:
        CARAMEL_NOT_REACHED();
    }
    

    this->LocateFollower();
}


void ScrollingNode::LocateFollower()
{
    switch ( m_orientation )
    {
    case ORIENTATION_HORIZONTAL:
    {
        const auto x = m_leader->getPositionX();
        const auto w = m_leader->getContentSize().width;

        if ( m_velocity > 0 )
        {
            m_follower->setPositionX( x - w );
        }
        else
        {
            m_follower->setPositionX( x + w );
        }
        break;
    }

    case ORIENTATION_VERTICAL:
        break;
    default:
        CARAMEL_NOT_REACHED();
    }

    //const auto pw = m_follower->getParent()->getContentSize().width;
    //const auto lx = m_leader->getPositionX();

    //if ( m_velocity > 0 )
    //{
    //    Locate( m_follower ).CenterY().X( lx - pw );
    //}
    //else
    //{
    //    Locate( m_follower ).CenterY().X( lx + pw );
}

#endif

///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle
