// Brittle C++ Library - Service - Localization Header

#ifndef __BRITTLE_SERVICE_LOCALIZATION_H
#define __BRITTLE_SERVICE_LOCALIZATION_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>
#include <Brittle/Utils/LanguageId.h>


namespace Brittle
{

///////////////////////////////////////////////////////////////////////////////
//
// Localization
//

class Localization
{
public:

    struct Settings;

    static void Initialize( const Settings& s );
    
    static void ChangeLanguage( const LanguageId& langId );

    static LanguageId GetCurrentLanguage();


private:

    Localization() = delete;
};


//
// Embedded Structs
//

enum ChineseSupportMode
{                               // Allowed language codes
    CHINESE_NONE         = 0,   //   (none)
    CHINESE_SINGLE       = 1,   //   zh
    CHINESE_BY_SCRITPING = 2,   //   zhs, zht
    CHINESE_BY_REGION    = 3,   //   zh-cn, zh-hk, zh-tw
};


struct Localization::Settings
{
    LanguageId defaultLanguage;
    std::vector< LanguageId > alternativeLanguages;
    ChineseSupportMode supportsChinese;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle

#endif // __BRITTLE_SERVICE_LOCALIZATION_H
