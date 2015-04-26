// Brittle C++ Library - Layout - Locate Header

#ifndef __BRITTLE_LAYOUT_LOCATE_H
#define __BRITTLE_LAYOUT_LOCATE_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>
#include <Brittle/Utils/JsonValue.h>
#include <Caramel/Error/Assert.h>
#include <2d/CCNode.h>


namespace Brittle
{

///////////////////////////////////////////////////////////////////////////////
//
// Locate Charm
//

class LocateCharm
{
public:
    explicit LocateCharm( Node* target );
    ~LocateCharm();

    void Apply();


    /// Add Attributes ///

    LocateCharm& Center();
    LocateCharm& CenterX();
    LocateCharm& CenterY();

    LocateCharm& X( Float x );
    LocateCharm& Y( Float y );

    LocateCharm& FromLeft  ( Float x );
    LocateCharm& FromRight ( Float x );
    LocateCharm& FromTop   ( Float y );
    LocateCharm& FromBottom( Float y );

    LocateCharm& FromLeftTop    ( Float x, Float y );
    LocateCharm& FromRightTop   ( Float x, Float y );
    LocateCharm& FromLeftBottom ( Float x, Float y );
    LocateCharm& FromRightBottom( Float x, Float y );

    LocateCharm& FromCenterX( Float x );
    LocateCharm& FromCenterY( Float y );

    LocateCharm& FromCenter( Float x, Float y );
    LocateCharm& FromCenter( const Vec2& v );


    // Read attributes from a JSON (which should be an Array)
    LocateCharm& Json( const JsonValue& json );


private:
    
    Node* m_target { nullptr };
    Bool  m_applied { false };

    enum UseFlag
    {
        USE_X_NORM          = 0x0001,  // 0.0 - 1.0
        USE_X_AT            = 0x0002,
        USE_X_FROM_LEFT     = 0x0004,
        USE_X_FROM_RIGHT    = 0x0008,
        USE_X_FROM_CENTER   = 0x0010,

        USE_Y_NORM          = 0x0100,  // 0.0 - 1.0
        USE_Y_AT            = 0x0200,
        USE_Y_FROM_TOP      = 0x0400,
        USE_Y_FROM_BOTTOM   = 0x0800,
        USE_Y_FROM_CENTER   = 0x1000,
    };

    Uint32 m_uses { 0 };

    Float m_paramX { 0 };
    Float m_paramY { 0 };
};


inline LocateCharm Locate( Node* target )
{
    return LocateCharm( target );
}


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

inline LocateCharm& LocateCharm::Center()
{
    m_uses |= USE_X_NORM | USE_Y_NORM;
    m_paramX = 0.5;
    m_paramY = 0.5;
    return *this;
}


inline LocateCharm& LocateCharm::CenterX()
{
    m_uses |= USE_X_NORM;
    m_paramX = 0.5;
    return *this;
}


inline LocateCharm& LocateCharm::CenterY()
{
    m_uses |= USE_Y_NORM;
    m_paramY = 0.5;
    return *this;
}


inline LocateCharm& LocateCharm::X( Float x )
{
    m_uses |= USE_X_AT;
    m_paramX = x;
    return *this;
}


inline LocateCharm& LocateCharm::Y( Float y )
{
    m_uses |= USE_Y_AT;
    m_paramY = y;
    return *this;
}


inline LocateCharm& LocateCharm::FromLeft( Float x )
{   
    m_uses |= USE_X_FROM_LEFT;
    m_paramX = x;
    return *this;
}


inline LocateCharm& LocateCharm::FromRight( Float x )
{   
    m_uses |= USE_X_FROM_RIGHT;
    m_paramX = x;
    return *this;
}


inline LocateCharm& LocateCharm::FromTop( Float y )
{
    m_uses |= USE_Y_FROM_TOP;
    m_paramY = y;
    return *this;
}


inline LocateCharm& LocateCharm::FromBottom( Float y )
{
    m_uses |= USE_Y_FROM_BOTTOM;
    m_paramY = y;
    return *this;
}


inline LocateCharm& LocateCharm::FromLeftTop( Float x, Float y )
{
    return this->FromLeft( x ).FromTop( y );
}


inline LocateCharm& LocateCharm::FromRightTop( Float x, Float y )
{
    return this->FromRight( x ).FromTop( y );
}


inline LocateCharm& LocateCharm::FromLeftBottom( Float x, Float y )
{
    return this->FromLeft( x ).FromBottom( y );
}


inline LocateCharm& LocateCharm::FromRightBottom( Float x, Float y )
{
    return this->FromRight( x ).FromBottom( y );
}


inline LocateCharm& LocateCharm::FromCenterX( Float x )
{
    m_uses |= USE_X_FROM_CENTER;
    m_paramX = x;
    return *this;
}


inline LocateCharm& LocateCharm::FromCenterY( Float y )
{
    m_uses |= USE_Y_FROM_CENTER;
    m_paramY = y;
    return *this;
}


inline LocateCharm& LocateCharm::FromCenter( Float x, Float y )
{
    return this->FromCenterX( x ).FromCenterY( y );
}


inline LocateCharm& LocateCharm::FromCenter( const Vec2& v )
{
    return this->FromCenterX( v.x ).FromCenterY( v.y );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle

#endif // __BRITTLE_LAYOUT_LOCATE_H
