// Brittle C++ Library - UI - Simple Button Header

#ifndef __BRITTLE_UI_SIMPLE_BUTTON_H
#define __BRITTLE_UI_SIMPLE_BUTTON_H
#pragma once

#include <Brittle/Setup/BrittleDefs.h>
#include <Brittle/Ui/UiTypes.h>
#include <ui/UIButton.h>


namespace Brittle
{

///////////////////////////////////////////////////////////////////////////////
//
// Simple Button
// - A button widget which has only a click event.
//

class SimpleButton : public ui::Button
                   , public Clickable
{
public:

    SimpleButton();


    //
    // Creating Functions
    // - Imitate the behavior of ui::Button.
    //

    static SimpleButton* Create();

    static SimpleButton* Create(
        const std::string& normalImabe,
        const std::string& selectedImage = "",
        const std::string& disabledImage = "",
        TextureResType texType = TextureResType::LOCAL
    );


    /// Event Handling ///

    void SetClickHandler( ClickHandler handler ) override;


private:

    void OnClickEvent( Ref* sender );

    ClickHandler m_clickHandler;

};


///////////////////////////////////////////////////////////////////////////////

} // namespace Brittle

#endif // __BRITTLE_UI_SIMPLE_BUTTON_H
