// Brittle C++ Library - Core Implementation

#include "BrittlePch.h"

#include "Core/AsyncCenter.h"
#include <Brittle/Core/Async.h>
#include <Brittle/Core/FrameClock.h>
#include <Brittle/Core/SimpleApp.h>
#include <Brittle/Core/SimpleScene.h>
#include <Brittle/Layout/Align.h>
#include <Brittle/Nodes/Listen.h>
#include <Caramel/Chrono/ClockProxy.h>
#include <Caramel/Error/CatchException.h>


namespace Brittle
{

//
// [Contents]
//
//   SimpleApp
//   SimpleScene
//   FrameClock
//   AsyncCenter
//   Async
//

///////////////////////////////////////////////////////////////////////////////
//
// Simple Application
//

SimpleApp::SimpleApp( const AppDesc& desc )
    : m_desc( desc )
{}


SimpleApp* SimpleApp::Instance()
{
    return static_cast< SimpleApp* >( Application::getInstance() );
}


//
// Application Event Handling
//

Bool SimpleApp::applicationDidFinishLaunching()
{
    TraceInfo( "Application Did Finish Launching" );

    auto director = Director::getInstance();

    /// Design Resolution ///

    const auto frameSize = director->getOpenGLView()->getFrameSize();

    // Aspect ratios
    const auto frameAr = frameSize.width / frameSize.height;
    const auto designAr = m_desc.designWidth / m_desc.designHeight;
    
    if ( frameAr > designAr )
    {
        director->getOpenGLView()->
            setDesignResolutionSize( 1, m_desc.designHeight, ResolutionPolicy::FIXED_HEIGHT );
    }
    else
    {
        director->getOpenGLView()->
            setDesignResolutionSize( m_desc.designWidth, 1, ResolutionPolicy::FIXED_WIDTH );
    }


    /// Initial Scene ///

    auto initialScene = this->CreateScene( m_desc.initialSceneId );
    director->pushScene( initialScene->GetScreen() );


    /// Animation and Schedule Update ///
    
    director->startAnimation();
    director->getScheduler()->scheduleUpdate( this, -1, false );


    /// Specify Default Search Path ///

    auto fileUtils = CCFileUtils::getInstance();
    fileUtils->addSearchPath( fileUtils->getWritablePath() );


    /// App Settings ///

    director->setDisplayStats( m_settings.enableDisplayStats );


    // Post event to the derived
    this->OnLaunch();

    return true;
}


void SimpleApp::applicationDidEnterBackground()
{
    TraceInfo( "App enter background" );

    Director::getInstance()->stopAnimation();

    this->OnEnterBackground();
}


void SimpleApp::applicationWillEnterForeground()
{
    TraceInfo( "App enter foreground" );

    Director::getInstance()->startAnimation();

    this->OnEnterForeground();
}


void SimpleApp::applicationWillTerminate()
{
    // Only desktop app will receive this event.
    TraceInfo( "App will terminate" );

    this->OnTerminate();
}


void SimpleApp::update( Float delta )
{
    FrameClock::Advance( delta );

    AsyncCenter::Instance()->RenderUpdate();
}


//
// Entry from Platform Dependent Scope
//

#if defined( BRITTLE_SYSTEM_IS_DESKTOP )

Int SimpleApp::Run( const AppSettings& settings )
{
    m_settings = settings;

    this->InitPlatform();

    auto xc = CatchException( [=] ()-> Int { return this->run(); } );
    if ( xc )
    {
        CARAMEL_ALERT( "Application::run() throws:\n{0}", xc.TracingMessage() );
        return EXIT_FAILURE;
    }

    this->ExitPlatform();

    return xc.Result();
}

#elif defined( BRITTLE_SYSTEM_IS_MOBILE )

void SimpleApp::Launch( const AppSettings& settings )
{
    m_settings = settings;

    this->InitPlatform();

    auto xc = CatchException( [=] ()-> Int { return this->run(); } );
    if ( xc )
    {
    	CARAMEL_ALERT( "Application::run() throws:\n{0}", xc.TracingMessage() );
    }
}

#endif  // BRITTLE_SYSTEM



//
// Scene Management
//

void SimpleApp::ReplaceScene( Int sceneId )
{
    auto newScene = this->CreateScene( sceneId );
    Director::getInstance()->replaceScene( newScene->GetScreen() );
}


//
// Properties
//

Size SimpleApp::GetDesignSize() const
{
    return Size( m_desc.designWidth, m_desc.designHeight );
}


///////////////////////////////////////////////////////////////////////////////
//
// Simple Scene
//

//
// Initialization
//

Bool SimpleScene::Init( Scene* screen )
{
    this->setContentSize( SimpleApp::Instance()->GetDesignSize() );
    this->setLocalZOrder( 1 );

    m_screen = screen;
    m_screen->setContentSize( Director::getInstance()->getVisibleSize() );
    m_screen->addChild( this );

    Align( this ).MiddleCenter();

    this->OnCreate();
    return true;
}


//
// Node Event Handling
//

void SimpleScene::onEnter()
{
    this->Node::onEnter();
 
    this->scheduleUpdate();

    m_keyboardListener = EventListenerKeyboard::create();
    m_keyboardListener->onKeyReleased = CC_CALLBACK_2( SimpleScene::OnKeyReleased, this );
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority( m_keyboardListener, this );

    this->OnEnterScene();
}


void SimpleScene::onExit()
{
    this->OnExitScene();

    this->getEventDispatcher()->removeEventListener( m_keyboardListener );

    this->unscheduleUpdate();

    this->Node::onExit();
}


void SimpleScene::update( Float delta )
{
    this->OnUpdate();
}


//
// Scene Management
//

void SimpleScene::ReplaceScene( Int sceneId )
{
    SimpleApp::Instance()->ReplaceScene( sceneId );
}


//
// Keyboard Events
//

void SimpleScene::OnKeyReleased( EventKeyboard::KeyCode key, Event* event )
{
	TraceInfo( "Key released: {0}", key );

    if ( key == EventKeyboard::KeyCode::KEY_BACK )
    {
        this->OnBackKeyPressed();
    }
}


//
// UI Utilities
//

LayerColor* SimpleScene::CreateScreenCover( const Color4B& color )
{
    const auto screenSize = m_screen->getContentSize();

    auto cover = LayerColor::create( color, screenSize.width, screenSize.height );
    cover->ignoreAnchorPointForPosition( false );
    cover->setLocalZOrder( this->getLocalZOrder() + 1 );
    Listen( cover ).SwallowTouchBegan();

    m_screen->addChild( cover );
    Align( cover ).MiddleCenter();
    return cover;
}


///////////////////////////////////////////////////////////////////////////////
//
// Frame Clock
//

Seconds FrameClock::m_sinceEpoch;
Bool FrameClock::m_paused = false;


void FrameClock::Pause()
{
    m_paused = true;
}


void FrameClock::Resume()
{
    m_paused = false;
}


FrameTime FrameClock::Now()
{
    return FrameTime( m_sinceEpoch );
}


void FrameClock::Advance( Float delta )
{
    if ( m_paused )
    {
        return;
    }

    m_sinceEpoch += Seconds( delta );
}


///////////////////////////////////////////////////////////////////////////////
//
// Frame Time
//

FrameTime::FrameTime( const Seconds& sinceEpoch )
    : Inherited( sinceEpoch )
{
}


///////////////////////////////////////////////////////////////////////////////
//
// Asynchronous Center
//

AsyncCenter::AsyncCenter()
    : m_renderPoller( new TaskPoller( ClockProxy( FrameClock() )))
{
}


void AsyncCenter::RenderUpdate()
{
    m_renderPoller->PollFor( Ticks( 10 ));
}


///////////////////////////////////////////////////////////////////////////////
//
// Asynchronous
//

TaskExecutor& Async::RenderExecutor()
{
    return AsyncCenter::Instance()->RenderExecutor();
}


void Async::RenderUpdate()
{
    AsyncCenter::Instance()->RenderUpdate();
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle
