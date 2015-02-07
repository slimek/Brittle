// Brittle C++ Library - Animation Implementation

#include "BrittlePch.h"

#include <Brittle/Animation/FlipbookAnimation.h>
#include <Brittle/Utils/Geometry.h>


namespace Brittle
{

//
// [Content]
//
//   FlipbookAnimationBuilder
//

///////////////////////////////////////////////////////////////////////////////
//
// Flipbook Animation Builder
//

typedef FlipbookAnimationBuilder FABuilder;

FABuilder& FlipbookAnimationBuilder::Files( std::string filePattern, Uint numFrames )
{
    m_filePattern = std::move( filePattern );
    m_numFrames = numFrames;
    return *this;
}


FABuilder& FlipbookAnimationBuilder::Indexes( std::vector< Uint > indexes )
{
    m_indexes = std::move( indexes );
    return *this;
}


FABuilder& FlipbookAnimationBuilder::DelayPerUnit( Float seconds )
{
    m_delayPerUnit = seconds;
    return *this;
}


FABuilder& FlipbookAnimationBuilder::UseAliasTexParameters()
{
    m_useAliasTexParameters = true;
    return *this;
}


Animation* FlipbookAnimationBuilder::Build()
{
    auto texCache = Director::getInstance()->getTextureCache();

    Vector< SpriteFrame* > frames;
    for ( Uint i = 0; i < m_numFrames; ++ i )
    {
        const auto filePath = Format( m_filePattern, i );
        auto tex = texCache->addImage( filePath );

        if ( m_useAliasTexParameters )
        {
            tex->setAliasTexParameters();
        }

        auto frame = SpriteFrame::createWithTexture( tex, MakeRect( tex->getContentSize() ));
        frames.pushBack( frame );            
    }

    if ( m_indexes.empty() )
    {
        return Animation::createWithSpriteFrames( frames, m_delayPerUnit );
    }
    else
    {
        auto anim = Animation::create();
        anim->setDelayPerUnit( m_delayPerUnit );

        for ( auto index : m_indexes )
        {
            anim->addSpriteFrame( frames.at( index ));
        }

        return anim;
    }
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle
