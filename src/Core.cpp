// Brittle C++ Library - Core Implementation

#include "BrittlePch.h"

#include "Core/AsyncCenter.h"
#include <Brittle/Core/Async.h>
#include <Brittle/Core/FrameClock.h>
#include <Brittle/Core/SimpleApp.h>
#include <Brittle/Core/SimpleScene.h>
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

SimpleApp* SimpleApp::Instance()
{
    return static_cast< SimpleApp* >( Application::getInstance() );
}


//
// Application Event Handling
//

Bool SimpleApp::applicationDidFinishLaunching()
{
    CARAMEL_TRACE_INFO( "Application Did Finish Launching" );

    this->OnLaunch();

    auto director = Director::getInstance();

    director->startAnimation();

    auto initialScene = this->CreateScene( m_settings.initialSceneId );
    director->pushScene( initialScene );


    /// Scheduler ///
    
    director->getScheduler()->scheduleUpdate( this, -1, false );


    /// Specify Default Search Path ///

    auto fileUtils = CCFileUtils::getInstance();
    fileUtils->addSearchPath( fileUtils->getWritablePath() );

    return true;
}


void SimpleApp::applicationDidEnterBackground()
{
    CARAMEL_TRACE_INFO( "App enter background" );

    Director::getInstance()->stopAnimation();

    this->OnEnterBackground();
}


void SimpleApp::applicationWillEnterForeground()
{
    CARAMEL_TRACE_INFO( "App enter foreground" );

    Director::getInstance()->startAnimation();

    this->OnEnterForeground();
}


void SimpleApp::applicationWillTerminate()
{
    // Only desktop app will receive this event.
    CARAMEL_TRACE_INFO( "App will terminate" );

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
    Director::getInstance()->replaceScene( newScene );
}


///////////////////////////////////////////////////////////////////////////////
//
// Simple Scene
//

//
// Node Event Handling
//

void SimpleScene::onEnter()
{
    this->Scene::onEnter();

    this->setContentSize( Director::getInstance()->getVisibleSize() );

    this->scheduleUpdate();

    m_keyboardListener = EventListenerKeyboard::create();
    m_keyboardListener->onKeyReleased = CC_CALLBACK_2( SimpleScene::OnKeyReleased, this );
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority( m_keyboardListener, this );

    this->OnEnterScene();
}


void SimpleScene::onExit()
{
    this->OnExitScene();

    // NOTES: Event listeners will auto-release when the scene destroyed.

    this->unscheduleUpdate();

    this->Scene::onExit();
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
