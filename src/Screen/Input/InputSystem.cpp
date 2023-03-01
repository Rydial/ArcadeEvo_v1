#include "InputSystem.h"

#include "Debug.h"

#include <SDL2/SDL.h>


////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// Input System /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


void InputSystem::update()
{
    // Update Mouse Input
    updateMouse();

    // Update Keyboard Input
    updateKeyboard();
}

/*************************** Update-Stage Functions ***************************/

void InputSystem::updateMouse()
{
    using namespace input;

    // Retrieve Mouse Inputs
    data::ivec2 rawPos     {                                       };
    uint32_t    mouseState {SDL_GetMouseState(&rawPos.x, &rawPos.y)};

    /***************************** Mouse Position *****************************/

    // Update Mouse Position
    input.mouse.pos.x =                  rawPos.x  - (*windowWidth  * 0.5f);
    input.mouse.pos.y = (*windowHeight - rawPos.y) - (*windowHeight * 0.5f);

    /***************************** Mouse Buttons ******************************/

    // Update Left Mouse Button (Mouse Button 1)
    processMouseButton(Mouse::LEFT, mouseState & SDL_BUTTON_LEFT);
    
    /* ...ad nauseum... */
}


void InputSystem::updateKeyboard() /* WIP */
{
    using namespace input;

    // Retrieve & Update Current Keyboard State
    const uint8_t* const keyState {SDL_GetKeyboardState(nullptr)};

    // Update Enter Key (Return Key)
    processKeyboardKey(Key::ENTER, keyState[SDL_SCANCODE_RETURN]);

    /* ...ad nauseum... */
}

/********************************* Functions **********************************/

void InputSystem::processMouseButton(input::Mouse type, bool clicked)
{
    using namespace input;
    auto& mouseBtnState {input[type]};

    // Mouse Button Click
    if (clicked)
    {
        switch (mouseBtnState)
        {
            case State::NONE:
                mouseBtnState = State::CLICKED;
                break;

            case State::CLICKED:
                mouseBtnState = State::HELD;
                break;

            default: break;
        }
    }

    // Mouse Button Release
    else
    {
        switch (mouseBtnState)
        {
            case State::CLICKED:
            case State::HELD:
                mouseBtnState = State::RELEASED;
                break;

            case State::RELEASED:
                mouseBtnState = State::NONE;
                break;
            
            default: break;
        }
    }
}


void InputSystem::processKeyboardKey(input::Key   type, bool pressed)
{
    using namespace input;
    auto& keyState {input[type]};

    // Key Press
    if (pressed)
    {
        switch (keyState)
        {
            case State::NONE:
                keyState = State::PRESSED;
                break;

            case State::PRESSED:
                keyState = State::HELD;
                break;

            default: break;
        }
    }

    // Key Release
    else
    {
        switch (keyState)
        {
            case State::PRESSED:
            case State::HELD:
                keyState = State::RELEASED;
                break;

            case State::RELEASED:
                keyState = State::NONE;
                break;
            
            default: break;
        }
    }
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
