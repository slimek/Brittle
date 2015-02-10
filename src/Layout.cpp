// Brittle C++ Library - Layout Implementation

#include "BrittlePch.h"

#include "Layout/LayoutJsonImpl.h"
#include "Layout/SpriteBuilder.h"
#include <Brittle/Layout/Locate.h>
#include <Brittle/Layout/Stretch.h>
#include <Brittle/Utils/Geometry.h>
#include <Macaron/RapidJson/JsonBelt.h>
#include <Macaron/RapidJson/JsonReader.h>
#include <Caramel/String/Algorithm.h>


namespace Brittle
{

//
// [Contents]
//
//   LocateCharm
//   StretchCharm
//   LayoutJson
//   SpriteBuilder
//

///////////////////////////////////////////////////////////////////////////////
//
// Locate Charm
//

LocateCharm::LocateCharm( Node* target )
    : m_target( target )
{
    CARAMEL_ASSERT( target );
    CARAMEL_ASSERT( target->getParent() );
}


LocateCharm::~LocateCharm()
{
    this->Apply();
}


void LocateCharm::Apply()
{
    if ( m_applied ) { return; }
    m_applied = true;

    const auto parent = m_target->getParent();
    const auto parentSize = parent->getContentSize();

    
    /// Determine X location ///

    if ( m_uses & USE_X_NORM )
    {
        m_target->setPositionX( m_paramX * parentSize.width );
    }
    else if ( m_uses & USE_X_FROM_LEFT )
    {
        m_target->setPositionX( m_paramX );
    }
    else if ( m_uses & USE_X_FROM_RIGHT )
    {
        m_target->setPositionX( parentSize.width - m_paramX );
    }


    /// Determine Y location ///

    if ( m_uses & USE_Y_NORM )
    {
        m_target->setPositionY( m_paramY * parentSize.height );
    }
    else if ( m_uses & USE_Y_FROM_TOP )
    {
        m_target->setPositionY( parentSize.height - m_paramY );
    }
    else if ( m_uses & USE_Y_FROM_BOTTOM )
    {
        m_target->setPositionY( m_paramY );
    }
}


LocateCharm& LocateCharm::Json( const JsonValue& json )
{
    if ( json.IsArray() )
    {
        Macaron::RapidJson::JsonBelt jb( json.AsArray() );

        // Attribute name
        std::string attr;

        try
        {
            while ( ! jb.IsEmpty() )
            {
                attr = jb.TakeString();

                #define ATTR( name, action ) \
                    else if ( attr == name ) { this->action; }

                if ( attr == "" )
                {
                    CARAMEL_ALERT( "Locate attribute name is empty" );
                }
                ATTR( "fromLeftTop",        FromLeftTop( (Float)jb, (Float)jb )     )
                ATTR( "fromRightTop",       FromRightTop( (Float)jb, (Float)jb )    )
                ATTR( "fromLeftBottom",     FromLeftBottom( (Float)jb, (Float)jb )  )
                ATTR( "fromRightBottom",    FromRightBottom( (Float)jb, (Float)jb ) )
                ATTR( "fromLeft",           FromLeft( (Float)jb )                   )
                ATTR( "fromRight",          FromRight( (Float)jb )                  )
                ATTR( "fromTop",            FromTop( (Float)jb )                    )
                ATTR( "fromBottom",         FromBottom( (Float)jb )                 )
                else
                {
                    CARAMEL_ALERT( "Unknown Locate attribute: %s", attr );
                }
            }
        }
        catch ( ... )
        {
            CARAMEL_ALERT( "Parse Locate in \"%s\" attribute", attr );
        }
    }

    return *this;
}


///////////////////////////////////////////////////////////////////////////////
//
// Stretch Charm
//

StretchCharm::StretchCharm( Node* target )
    : m_target( target )
{
    CARAMEL_ASSERT( target );
    CARAMEL_ASSERT( target->getParent() );
}


StretchCharm::~StretchCharm()
{
    this->Apply();
}


void StretchCharm::Apply()
{
    if ( m_applied ) { return; }
    m_applied = true;

    const auto parent = m_target->getParent();
    if ( ! parent )
    {
        CARAMEL_ALERT( "You must set parent before using Stretch()" );
        return;
    }

    const auto parentSize = parent->getContentSize();
    auto targetSize = m_target->getContentSize();
    
    const Float scalingX = parentSize.width / targetSize.width;
    const Float scalingY = parentSize.height / targetSize.height;

    /// Stretch ///

    switch ( m_stretchMethod )
    {
    case STRETCH_UNDEF: // default
    case STRETCH_FILL:
    {
        m_target->setScale( std::max( scalingX, scalingY ));
        break;
    }

    case STRETCH_FIT:
    {
        m_target->setScale( std::min( scalingX, scalingY ));
        break;
    }

    case STRETCH_AUTO:
    {
        m_target->setScaleX( scalingX );
        m_target->setScaleY( scalingY );
        break;
    }

    case STRETCH_REPEAT:
    {
        this->ApplyRepeat();
        break;
    }

    case STRETCH_NONE:
    {
        // Do nothing, keep the original size.
        return;
    }
    
    default:
        CARAMEL_THROW( "Unknown stretch method: %d", m_stretchMethod );
    }

    /// Align ///

    const auto center = GetCenter( parent->getContentSize() );
    m_target->setPosition( center );
}


void StretchCharm::ApplyRepeat()
{
    // NOTES: The target has been already stretched to the parent's content area in Apply().

    auto sprite = dynamic_cast< Sprite* >( m_target );
    if ( ! sprite )
    {
        CARAMEL_ALERT( "The target is not a sprite" );
        return;
    }

    auto texture = sprite->getTexture();
    if ( ! texture )
    {
        CARAMEL_ALERT( "The target sprite doesn't have a texture" );
        return;
    }

    const Texture2D::TexParams texp{ GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT };
    texture->setTexParameters( texp );

    // Let the repeating starts from the center of the parent.             X | X
    // I.e. at the parent center, the texture coord is ( 0, 0 ).           --+--
    // And the distance of texture coords equal to parent's dimensions.    X | X

    const auto parSize = m_target->getParent()->getContentSize();
    const auto w = parSize.width;
    const auto h = parSize.height;

    sprite->setTextureRect( { - w / 2, - h / 2, w, h } );
}


///////////////////////////////////////////////////////////////////////////////
//
// Layout JSON
//

LayoutJson::LayoutJson( const std::string& filePath )
{
    auto fileUtils = FileUtils::getInstance();
    
    if ( ! fileUtils->isFileExist( filePath ))
    {
        CARAMEL_THROW( "Layout file \"%s\" not found", filePath );
    }

    const std::string jsonText = fileUtils->getStringFromFile( filePath );

    Macaron::RapidJson::JsonReader reader;
    JsonValue json;

    if ( ! reader.Parse( jsonText, json ))
    {
        CARAMEL_THROW( "%s is not a valid JSON", filePath );
    }

    m_impl.reset( new LayoutJsonImpl( filePath, json ));
}


LayoutJson::LayoutJson( const std::string& name, const std::string& jsonText )
{
    Macaron::RapidJson::JsonReader reader;
    JsonValue json;

    if ( ! reader.Parse( jsonText, json ))
    {
        CARAMEL_THROW( "%s embedded layout is not a valid JSON", name );
    }

    m_impl.reset( new LayoutJsonImpl( name, json ));
}


Sprite* LayoutJson::AddSprite( Node* node, const std::string& name )
{
    JsonValue json;
    if ( ! m_impl->GetItem( name, json ))
    {
        CARAMEL_THROW( "In layout \"%s\" the \"%s\" not found", m_impl->GetName(), name );
    }

    std::string imagePath;
    if ( ! json.GetString( "image", imagePath ))
    {
        CARAMEL_THROW( "In layout \"%s\" the \"s\" has no image, can't create a Sprite",
                       m_impl->GetName(), name );
    }

    SpriteBuilder builder( node, imagePath );
    if ( ! builder.Parse( json ))
    {
        CARAMEL_THROW( "In layout \"s\" the \"s\" create sprite failed",
                       m_impl->GetName(), name );
    }
    return builder.GetSprite();
}


//
// Implementation
//

LayoutJsonImpl::LayoutJsonImpl( const std::string& name, const JsonValue& json )
    : m_name( name )
    , m_json( json )
{
}


Bool LayoutJsonImpl::GetItem( const std::string& itemName, JsonValue& item ) const
{
    return m_json.GetValue( itemName, item );
}


///////////////////////////////////////////////////////////////////////////////
//
// Sprite Builder
//

SpriteBuilder::SpriteBuilder( Node* parent, const std::string& imagePath )
{
    m_sprite = Sprite::create( imagePath );
    parent->addChild( m_sprite );
}


SpriteBuilder::~SpriteBuilder()
{
    if ( m_failed )
    {
        m_sprite->removeFromParent();
        
        // Since the sprite is autoreleased, we don't need to release it.
    }
}


Bool SpriteBuilder::Parse( const JsonValue& layoutJson )
{
    JsonValue json;
    if ( layoutJson.GetValue( "position", json ))
    {
        LocateCharm( m_sprite ).Json( json );
    }

    return true;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle
