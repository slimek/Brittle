// Brittle C++ Library - Utils Win32 Dependent Implementation

#include "BrittlePch.h"

#include <Brittle/Utils/LanguageId.h>
#include <Caramel/String/Algorithm.h>
#include <Caramel/Windows/WideString.h>
#include <Windows.h>


namespace Brittle
{

//
// [Contents]
//
//  LanguageId
//

///////////////////////////////////////////////////////////////////////////////
//
// Language ID
//

LanguageId LanguageId::FromSystem()
{
    /// Get System Language by Win32 API ///

    Wchar localeNameBuf[ LOCALE_NAME_MAX_LENGTH ] = { 0 };

    const Int size1 = ::GetUserDefaultLocaleName( &localeNameBuf[0], sizeof( localeNameBuf ));
    if ( size1 == 0 )
    {
        CARAMEL_THROW( "GetUserDefaultLocaleName() failed" );
    }

    const std::string localeName =
        Windows::WideString( localeNameBuf ).ToNarrow( TEXT_ENCODING_UTF8 );

    // Determine Chinese variants
    if ( localeName.substr( 0, 2 ) == "zh" )
    {
        if ( localeName == "zh-TW" )
        {
            // Taiwan
            return LanguageId::ZH_TW;
        }
        else if ( localeName == "zh-CN" || localeName == "zh-SG" )
        {
            // China and Singapore
            return LanguageId::ZH_CN;
        }
        else if ( localeName == "zh-HK" || localeName == "zh-MO" )
        {
            // Hongkong and Macau
            return LanguageId::ZH_HK;
        }
        else
        {
            return LanguageId::ZH;
        }
    }

    // For other language, get the language part before '-'.
    // If the code is not 2 alphabet, treat it as "unknown".

    const std::string langPart = BeforeFirst( localeName, '-' );

    if ( langPart.length() != 2 )
    {
        return LanguageId();
    }

    return LanguageId( langPart );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle
