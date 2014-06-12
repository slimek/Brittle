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


    /// Scene Management ///

    static void ReplaceScene( Int sceneId );


private:

    /// Game Scene Events ///

    virtual void OnEnterScene() {}
    virtual void OnExitScene()  {}
};


///////////////////////////////////////////////////////////////////////////////


} // namespace Brittle

#endif // __BRITTLE_CORE_SIMPLE_SCENE_H
