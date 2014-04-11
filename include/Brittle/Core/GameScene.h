// Brittle C++ Library - Core - Game Scene Header

#ifndef __BRITTLE_CORE_GAME_SCENE_H
#define __BRITTLE_CORE_GAME_SCENE_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>


namespace Brittle
{

///////////////////////////////////////////////////////////////////////////////
//
// Game Scene
//

class GameScene : public Scene
{
public:

    /// Node Events ///

    void onEnter() override;


private:

    /// Game Scene Events ///

    virtual void OnEnterScene() {}
};


///////////////////////////////////////////////////////////////////////////////


} // namespace Brittle

#endif // __BRITTLE_CORE_GAME_SCENE_H
