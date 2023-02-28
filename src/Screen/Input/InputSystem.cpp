#include "InputSystem.h"

#include "Debug.h"

#include <SDL2/SDL.h>


////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// Input System /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


void InputSystem::update()
{
    /****************************** Mouse Input *******************************/

    // Retrieve Mouse Inputs
    data::ivec2 rawPos     {                                       };
    uint32_t    mouseState {SDL_GetMouseState(&rawPos.x, &rawPos.y)};

    // Update Current Mouse Position
    current.mouse.pos.x =                  rawPos.x  - (*windowWidth  * 0.5f);
    current.mouse.pos.y = (*windowHeight - rawPos.y) - (*windowHeight * 0.5f);

    // Update Current Mouse Buttons
    current[input::Mouse::LEFT] = mouseState & SDL_BUTTON_LMASK;
    /* ...ad nauseum... */

    /***************************** Keyboard Input *****************************/

    // Retrieve & Update Current Keyboard State
    // const uint8_t* const keyState {SDL_GetKeyboardState(nullptr)};
    /* ...ad nauseum... */
}

/******************************** Constructors ********************************/

InputSystem::InputSystem(
    uint32_t* const windowWidth,
    uint32_t* const windowHeight)
  :
    windowWidth{windowWidth}, windowHeight{windowHeight}
{
    DEBUG_ASSERT(this->windowWidth  != nullptr);
    DEBUG_ASSERT(this->windowHeight != nullptr);
}
