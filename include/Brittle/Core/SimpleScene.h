// Brittle C++ Library - Core - Simple Scene Header

#ifndef __BRITTLE_CORE_SIMPLE_SCENE_H
#define __BRITTLE_CORE_SIMPLE_SCENE_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>


namespace Brittle
{

///////////////////////////////////////////////////////////////////////////////
//
// Simple Scene
//

class SimpleScene : public Scene
{
public:

    /// Node Events ///

    void onEnter() override;
    void onExit()  override;
    void update( Float delta ) override;


    /// Scene Management ///

    // Create a derived SimpleScene.
    // - It has been autoreleased.
    template< typename SceneType, typename... Args >
    static SceneType* Create( Args&&... args );

    // Create a derived SimpleScene and build the physics world.
    // - It has been autoreleased.
    template< typename SceneType, typename... Args >
    static SceneType* CreateWithPhysics( Args&&... args );

    // Call current SimpleApp to replace scene.
    static void ReplaceScene( Int sceneId );


private:

    /// Scene Events ///

    virtual void OnEnterScene() {}
    virtual void OnExitScene()  {}
    virtual void OnUpdate() {}


    /// Keyboard Events ///

    virtual void OnKeyReleased( EventKeyboard::KeyCode key, Event* event );
    
    // The "Back button" is pressed.
    // - Desktop : ESC key
    //   Android : Back button
    //   iOS     : (none)
    virtual void OnBackKeyPressed() {}


    /// Members ///

    EventListenerKeyboard* m_keyboardListener { nullptr };
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

template< typename SceneType, typename... Args >
inline SceneType* SimpleScene::Create( Args&&... args )
{
    auto scene = new SceneType( std::forward< Args >( args )... );
    if ( scene && scene->init() )
    {
        scene->autorelease();
        return scene;
    }
    else
    {
        delete scene;
        return nullptr;
    }
}


template< typename SceneType, typename... Args >
inline SceneType* SimpleScene::CreateWithPhysics( Args&&... args )
{
    auto scene = new SceneType( std::forward< Args >( args )... );
    if ( scene && scene->initWithPhysics() )
    {
        scene->autorelease();
        return scene;
    }
    else
    {
        delete scene;
        return nullptr;
    }
}


///////////////////////////////////////////////////////////////////////////////


} // namespace Brittle

#endif // __BRITTLE_CORE_SIMPLE_SCENE_H
