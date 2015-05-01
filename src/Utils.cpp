// Brittle C++ Library - Utilities Implementation

#include "BrittlePch.h"

#include <Brittle/Utils/Geometry.h>
#include <Brittle/Utils/LanguageId.h>
#include <Brittle/Utils/Styling.h>
#include <Caramel/Numeric/UnionBits.h>
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <algorithm>
#include <cctype>
#include <regex>


namespace Brittle
{

//
// [Contents[
//
//  MakeColor
//  LanguageId
//  ToString for cocos2d types
//

///////////////////////////////////////////////////////////////////////////////
//
// Make Color
//

Color3B MakeColor3B( Uint32 hexColor )
{
    // Format: RGB, lower 24-bit

    UnionBits32 b32;
    b32.ui = hexColor;
    return Color3B( b32.qb.mh, b32.qb.ml, b32.qb.lo );
}


Color4B MakeColor4B( Uint32 hexColor )
{
    // Format: RGBA

    UnionBits32 b32;
    b32.ui = hexColor;
    return Color4B( b32.qb.hi, b32.qb.mh, b32.qb.ml, b32.qb.lo );
}


///////////////////////////////////////////////////////////////////////////////
//
// Language ID
//

const LanguageId LanguageId::EN( "en" );
const LanguageId LanguageId::ZH( "zh" );
const LanguageId LanguageId::ZHS( "zhs" );
const LanguageId LanguageId::ZHT( "zht" );
const LanguageId LanguageId::ZH_CN( "zh-cn" );
const LanguageId LanguageId::ZH_HK( "zh-hk" );
const LanguageId LanguageId::ZH_TW( "zh-tw" );

LanguageId::LanguageId( std::string code )
{
    // To lower case, replace '_' with '-'.
    boost::algorithm::to_lower( code );
    boost::replace_all( code, "_", "-" );

    // Check if it is valid Chinese language ID.
    std::regex chinese( "zh(s|t|-ch|-hk|-tw)" );
    if ( std::regex_match( code, chinese ))
    {
        m_code = std::move( code );
        return;
    }
    
    // Codes more than 2 characters are treated as unknown.
    // (keep the m_code empty).
    if ( code.length() != 2 ) { return; }

    // Codes can only be alphabets
    if ( ! std::all_of( code.begin(), code.end(), isalpha ))
    {
        return;
    }

    // Then store the code.
    m_code = std::move( code );
}


//
// Operators
//

Bool LanguageId::operator==( const LanguageId& rhs ) const
{
    return m_code == rhs.m_code;
}


Bool LanguageId::operator<( const LanguageId& rhs ) const
{
    return m_code < rhs.m_code;
}


//
// Chinese Predicates
//

Bool LanguageId::IsChinese() const
{
    return m_code.substr( 0, 2 ) == "zh";
}


} // namespace Brittle


///////////////////////////////////////////////////////////////////////////////
//
// To String Functions for cocos2d Types
//

namespace cocos2d
{

std::string ToString( const cocos2d::Vec2& vec )
{
    return Caramel::Format( "({0}, {1})", vec.x, vec.y );
}


std::string ToString( const cocos2d::Size& size )
{
    return Caramel::Format( "({0}, {1})", size.width, size.height );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace cocos2d
