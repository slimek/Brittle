// Brittle C++ Library - Utils - Language ID Header

#ifndef __BRITTLE_UTILS_LANGUAGE_ID_H
#define __BRITTLE_UTILS_LANGUAGE_ID_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>
#include <boost/operators.hpp>


namespace Brittle
{

///////////////////////////////////////////////////////////////////////////////
//
// Language ID
// - Based on ISO 639-1, the 2-alphabet codes.
//   Further more, it has some specialization for Chinese.
//

class LanguageId : public boost::totally_ordered< LanguageId >
{
public:

    LanguageId() {}  // an empty code means "unknown".

    explicit LanguageId( std::string code );  // only two alphabets
                                              // (except for the below Chinese codes).

    // Get the current system language.
    // - The implementation depends on each system.
    static LanguageId FromSystem();


    /// Predefined Ids ///

    static const LanguageId EN;     // "en"  : English
    static const LanguageId ZH;     // "zh"  : Chinese (include all variants)

    // Chinese by Scriptings
    static const LanguageId ZHS;    // "zhs" : Simplified Chinese
    static const LanguageId ZHT;    // "zht" : Traditional Chinese
    
    // Chinese by Regions
    static const LanguageId ZH_CN;  // "zh-cn" : China    (Simplified)
    static const LanguageId ZH_HK;  // "zh-hk" : Hongkong (Traditional)
    static const LanguageId ZH_TW;  // "zh-tw" : Taiwan   (Traditional)


    /// Operators ///

    Bool operator==( const LanguageId& rhs ) const;
    Bool operator< ( const LanguageId& rhs ) const;


    /// Chinese Predicates ///

    Bool IsChinese() const;


    /// Properties ///

    Bool IsUnknown() const { return m_code.empty(); }
    std::string ToString() const { return m_code; }


private:
   
    std::string m_code;    
};


///////////////////////////////////////////////////////////////////////////////
//
// Appendix - The rule to parse the system locale information.
//
// Android
//
//   Not implemented yet.
//
// iOS/OS X
//
//   Not implemented yet.
//
// Windows
//
//   1. GetUserDefaultLocaleName() returns RFC 4646 language tags.
//      The format is <language>-<REGION>, like "en-US", "zh-TW".. etc.
//   2. For Chinese, we convert "zh-TW" to "zh-tw" (region becomes lowercase).
//   3. For other languages, we remove the region part,
//      i.e. "en-US" becomes "en".
//

///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle

#endif // __BRITTLE_UTILS_LANGUAGE_ID_H
