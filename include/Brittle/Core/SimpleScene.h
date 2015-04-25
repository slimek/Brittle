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

class SimpleScene : public Node
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


    Scene* GetScreen() const { return m_screen; }


    /// UI Utilities ///

    // Return a Layer with:
    //   1. Child of screen.
    //   2. Size of screen.
    //   3. At the center of screen.
    //   4. Local Z-order is 1 (in front of the Scene).
    //   5. Swallows all touch events.
    //   6. Color is what you give.
    LayerColor* CreateScreenCover( const Color4B& color );


protected:

    Scene* m_screen { nullptr };


private:

    Bool Init( Scene* screen );


    /// Scene Events ///

    virtual void OnCreate() {}
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
    if ( scene && scene->Init( Scene::create() ))
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
    if ( scene && scene->Init( Scene::createWithPhysics() ))
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
