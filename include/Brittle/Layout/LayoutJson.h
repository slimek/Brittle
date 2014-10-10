// Brittle C++ Library - Layout - Layout JSON Header

#ifndef __BRITTLE_LAYOUT_LAYOUT_JSON_H
#define __BRITTLE_LAYOUT_LAYOUT_JSON_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>
#include <2d/CCSprite.h>


namespace Brittle
{

///////////////////////////////////////////////////////////////////////////////
//
// Layout JSON
//

class LayoutJsonImpl;

class LayoutJson
{
public:
    
    explicit LayoutJson( const std::string& filePath );
    LayoutJson( const std::string& name, const std::string& jsonText );


    /// Create Display Objects ///

    Sprite* AddSprite( Node* node, const std::string& name );
    Sprite* AddSprite( Node* node, const std::string& name, const std::string& imagePath );


private:

    std::shared_ptr< LayoutJsonImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle

#endif // __BRITTLE_LAYOUT_LAYOUT_JSON_H
