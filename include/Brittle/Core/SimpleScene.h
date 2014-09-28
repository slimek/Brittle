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

    static void ReplaceScene( Int sceneId );


private:

    /// Scene Events ///

    virtual void OnEnterScene() {}
    virtual void OnExitScene()  {}
    virtual void OnUpdate() {}


    /// Keyboard Events ///

    virtual void OnKeyPressed( EventKeyboard::KeyCode key, Event* event );
    
    // The "Back button" is pressed.
    // - Desktop : ESC key
    //   Android : Back button
    //   iOS     : (none)
    virtual void OnBackKeyPressed() {}


    /// Members ///

    EventListenerKeyboard* m_keyboardListener { nullptr };
};


///////////////////////////////////////////////////////////////////////////////


} // namespace Brittle

#endif // __BRITTLE_CORE_SIMPLE_SCENE_H
