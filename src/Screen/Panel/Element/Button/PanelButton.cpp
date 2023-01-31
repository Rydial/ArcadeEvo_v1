#include "PanelButton.h"

#include "Debug.h"
#include "ExitCodes.h"
#include "UserInputs.h"

#include <SDL2/SDL.h>


////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// Panel Button /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


uint32_t panel::Button::processUserInput()
{
    /****************************** Mouse Click *******************************/

    // Get Mouse State
    int xPos {}, yPos {};
    [[maybe_unused]] uint32_t buttons {SDL_GetMouseState(&xPos, &yPos)};


    // Validate Mouse Click 1 (Left)
    if (buttons & SDL_BUTTON_LMASK)
    {
        DEBUG_PRINT("Mouse 1 Click");
    }

    /**************************************************************************/

    return exitcode::CONT_PROGRAM;
}
