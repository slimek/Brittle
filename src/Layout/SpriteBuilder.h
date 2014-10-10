// Brittle C++ Library - Layout - Sprite Builder Header

#ifndef __BRITTLE_LAYOUT_SPRITE_BUILDER_H
#define __BRITTLE_LAYOUT_SPRITE_BUILDER_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>
#include <Brittle/Utils/JsonValue.h>
#include <2d/CCSprite.h>


namespace Brittle
{

///////////////////////////////////////////////////////////////////////////////
//
// Sprite Builder
//

class SpriteBuilder
{
public:
    SpriteBuilder( Node* parent, const std::string& imagePath );
    ~SpriteBuilder();

    Bool Parse( const JsonValue& layoutJson );

    Sprite* GetSprite() const { return m_sprite; }

private:
    
    Sprite* m_sprite { nullptr };
    Bool m_failed { false };
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle

#endif // __BRITTLE_LAYOUT_SPRITE_BUILDER_H
