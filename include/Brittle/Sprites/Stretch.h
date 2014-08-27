// Brittle C++ Library - Sprites - Stretch Header

#ifndef __BRITTLE_SPRITES_STRETCH_H
#define __BRITTLE_SPRITES_STRETCH_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>
#include <2d/CCNode.h>


namespace Brittle
{

class StretchNode : public Node
{
public:
    
};


class Stretch
{
public:

    explicit Stretch( Node* node );

    operator Node*() const;
};


} // namespace Brittle

#endif // __BRITTLE_SPRITES_STRETCH_H
