// Brittle C++ Library - Nodes Implementation

#include "BrittlePch.h"

#include <Brittle/Core/SimpleScene.h>
#include <Brittle/Nodes/EllipseTouchable.h>
#include <Brittle/Nodes/HorizontalScrolling.h>
#include <Brittle/Nodes/Listen.h>
#include <Brittle/Nodes/NodeExtensions.h>
#include <Brittle/Nodes/ScreenCover.h>
#include <Brittle/Layout/Align.h>
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
//   ScreenCover
//   ListenCharm
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


///////////////////////////////////////////////////////////////////////////////
//
// Screen Cover
//

ScreenCover* ScreenCover::Create( SimpleScene* scene )
{
    CARAMEL_CHECK( scene );

    auto cover = MakeUnique< ScreenCover >();
    CARAMEL_CHECK( cover->InitWithScene( scene ));

    return cover.release();
}


Bool ScreenCover::InitWithScene( SimpleScene* scene )
{
    if ( ! this->init() ) { return false; }

    const auto screen = scene->GetScreen();
    const auto size = screen->getContentSize();

    this->ignoreAnchorPointForPosition( false );
    this->setLocalZOrder( Z_ORDER_SCREEN_COVER );
    Listen( this ).SwallowTouchBegan();

    screen->addChild( this );
    Align( this ).MiddleCenter();
    return true;
}


///////////////////////////////////////////////////////////////////////////////
//
// Listen Charm
//

ListenCharm::ListenCharm( Node* listenee )
    : m_listenee( listenee )
{}


ListenCharm::~ListenCharm()
{
    if ( ! m_applied )
    {
        this->Apply();
    }
}


ListenCharm& ListenCharm::SwallowTouchBegan()
{
    m_touchBegan = [] ( Touch*, Event* ) { return true; };
    return *this;
}


void ListenCharm::Apply()
{
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches( true );

    if ( m_touchBegan )
    {
        listener->onTouchBegan = m_touchBegan;
    }

    m_listenee->getEventDispatcher()
        ->addEventListenerWithSceneGraphPriority( listener, m_listenee );

    m_applied = true;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle
