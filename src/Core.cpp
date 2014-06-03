// Brittle C++ Library - Core Implementation

#include "BrittlePch.h"

#include <Brittle/Core/GameApp.h>
#include <Brittle/Core/GameScene.h>
#include <Brittle/Core/Model.h>
#include <Caramel/Error/CatchException.h>


namespace Brittle
{

//
// [Contents]
//
//   GameApp
//   GameScene
//   Model
//

///////////////////////////////////////////////////////////////////////////////
//
// Game Application
//

GameApp* GameApp::Instance()
{
    return static_cast< GameApp* >( Application::getInstance() );
}


//
// Application Event Handling
//

Bool GameApp::applicationDidFinishLaunching()
{
    CARAMEL_TRACE_INFO( "Application Did Finish Launching" );

    this->OnLaunch();

    auto initialScene = this->CreateScene( m_settings.initialSceneId );
    initialScene->autorelease();
    Director::getInstance()->pushScene( initialScene );


    /// Specify Default Search Path ///

    auto fileUtils = CCFileUtils::getInstance();
    fileUtils->addSearchPath( fileUtils->getWritablePath() );

    return true;
}


void GameApp::applicationDidEnterBackground()
{
    this->OnEnterBackground();
}


void GameApp::applicationWillEnterForeground()
{
    this->OnEnterForeground();
}


//
// Entry from Platform Dependent Scope
//

Int GameApp::Run( const GameAppSettings& settings )
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

void GameApp::ReplaceScene( Int sceneId )
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
    GameApp::Instance()->ReplaceScene( sceneId );
}


///////////////////////////////////////////////////////////////////////////////
//
// Model
//

void Model::LinkEventTarget( AnyEventTarget& target )
{
    m_dispatcher.LinkTarget( target );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle
