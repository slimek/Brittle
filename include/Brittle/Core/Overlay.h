// Brittle C++ Library - Core - Overlay Header

#ifndef __BRITTLE_CORE_OVERLAY_H
#define __BRITTLE_CORE_OVERLAY_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>


namespace Brittle
{

// Forwards declaration
struct IAlertDialog;
struct IDialog;
struct IIndicator;
struct IToast;
class ScreenCover;

///////////////////////////////////////////////////////////////////////////////
//
// Overlay
//

class Overlay
{
public:

    static void AddDialog( IDialog* dialog, ScreenCover* cover = nullptr );

    static void AddIndicator( IIndicator* indicator );
    static void AddToast( IToast* toast );

    static void SetAlertDialog( IAlertDialog* dialog, ScreenCover* cover = nullptr );


private:
    Overlay() = delete;
};


///////////////////////////////////////////////////////////////////////////////
//
// Overlay Interfaces
//

struct IDialog : public Node
{
    virtual ~IDialog() {}

    virtual void Show() = 0;
    virtual void Hide() = 0;
};


struct IIndicator : public Node
{
    virtual ~IIndicator() {}

    virtual void Show() = 0;
    virtual void Hide() = 0;
};


struct IAlertDialog : public IDialog
{
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle

#endif // __BRITTLE_CORE_OVERLAY_H
