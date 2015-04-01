// Brittle C++ Library - UI - Label Button Header

#ifndef __BRITTLE_UI_LABEL_BUTTON_H
#define __BRITTLE_UI_LABEL_BUTTON_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>
#include <Brittle/ui/UiTypes.h>
#include <ui/UIText.h>


namespace Brittle
{

///////////////////////////////////////////////////////////////////////////////
//
// Label Button
// - A button widget which has only a Label, no image.
//

class LabelButton : public ui::Text
                  , public Clickable
{
public:
    
    LabelButton();


    //
    // Creating Functions
    //

    static LabelButton* Create();


    /// Event Handling ///

    void SetClickHandler( ClickHandler handler ) override;


private:

    void OnClickEvent( Ref* sender );

    ClickHandler m_clickHandler;
};
                

///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle

#endif // __BRITTLE_UI_LABEL_BUTTON_H
