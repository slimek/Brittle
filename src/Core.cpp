// Brittle C++ Library - Core Implementation

#include "BrittlePch.h"

#include "Core/AsyncCenter.h"
#include <Brittle/Core/Async.h>
#include <Brittle/Core/SimpleApp.h>
#include <Brittle/Core/GameScene.h>
#include <Caramel/Error/CatchException.h>


namespace Brittle
{

//
// [Contents]
//
//   SimpleApp
//   GameScene
//   AsyncCenter
//   Async
//

///////////////////////////////////////////////////////////////////////////////
//
// Game Application
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

    auto initialScene = this->CreateScene( m_settings.initialSceneId );
    initialScene->autorelease();
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
    this->OnEnterBackground();
}


void SimpleApp::applicationWillEnterForeground()
{
    this->OnEnterForeground();
}


void SimpleApp::update( Float delta )
{
    AsyncCenter::Instance()->RenderUpdate();
}


//
// Entry from Platform Dependent Scope
//

Int SimpleApp::Run( const GameAppSettings& settings )
{
    m_settings = settings;

    this->InitPlatform();

    auto xc = CatchException( [=] ()-> Int { return this->run(); } );
    if ( xc )
    {
        CARAMEL_ALERT( "Application::run() throws:\n%s", xc.TracingMessage() );
        return EXIT_FAILURE;
    }

    this->ExitPlatform();

    return xc.Result();
}


//
// Scene Management
//

void SimpleApp::ReplaceScene( Int sceneId )
{
    auto newScene = this->CreateScene( sceneId );
    newScene->autorelease();
    Director::getInstance()->replaceScene( newScene );
}


///////////////////////////////////////////////////////////////////////////////
//
// Game Scene
//

//
// Node Event Handling
//

void GameScene::onEnter()
{
    this->Scene::onEnter();

    this->setContentSize( Director::getInstance()->getVisibleSize() );

    this->OnEnterScene();
}


void GameScene::onExit()
{
    this->Scene::onExit();

    this->OnExitScene();
}


//
// Scene Management
//

void GameScene::ReplaceScene( Int sceneId )
{
    SimpleApp::Instance()->ReplaceScene( sceneId );
}


///////////////////////////////////////////////////////////////////////////////
//
// Asynchronous Center
//

AsyncCenter::AsyncCenter()
    : m_renderPoller( new TaskPoller )
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
