#ifndef SRC_INPUT_SYSTEM_H
#define SRC_INPUT_SYSTEM_H


#include "DataStructs.h"
#include "UserInput.h"


////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// Input System /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


class InputSystem
{
private:

    /****************************** Data Structs ******************************/

    struct MouseData
    {
        data::vec2   pos;
        input::State btns[static_cast<uint8_t>(input::Mouse::COUNT)];
    };


    struct KeyboardData
    {
        input::State key[static_cast<uint8_t>(input::Key::COUNT)];
    };


    struct InputData
    {
        MouseData    mouse;
        KeyboardData keyboard;

        input::State&       operator[](input::Mouse type)
        {
            return mouse.btns[static_cast<uint8_t>(type)];
        }
        const input::State& operator[](input::Mouse type) const
        {
            return mouse.btns[static_cast<uint8_t>(type)];
        }
        input::State&       operator[](input::Key type)
        {
            return keyboard.key[static_cast<uint8_t>(type)];
        }
        const input::State& operator[](input::Key type) const
        {
            return keyboard.key[static_cast<uint8_t>(type)];
        }
    };

    /****************************** Raw Pointers ******************************/

    uint32_t* const windowWidth  {};
    uint32_t* const windowHeight {};

    /******************************* Variables ********************************/

    InputData input {};

    /************************* Update-Stage Functions *************************/

    void updateMouse();
    void updateKeyboard();

    /******************************* Functions ********************************/

    /*
    
    */
    void processMouseButton(input::Mouse type, bool clicked);


    /*
    
    */
    void processKeyboardKey(input::Key   type, bool pressed);

public:

    /***************************** Main Functions *****************************/

    void update();

    /******************************* Functions ********************************/

    /*
        Returns whether the specified mouse input has been clicked down.
    */
    bool isClicked(input::Mouse type) const
    {
        return input[type] == input::State::CLICKED;
    }


    /*
        Returns whether the specified key input has been pressed down.
    */
    bool isPressed(input::Key type) const
    {
        return input[type] == input::State::CLICKED;
    }

    /*
        Returns whether the specified input has been released.
    */
    bool isReleased(input::Mouse type) const
    {
        return input[type] == input::State::RELEASED;
    }
    bool isReleased(input::Key   type) const
    {
        return input[type] == input::State::RELEASED;
    }

    /******************************** Getters *********************************/

    /*
        Returns a pair of references to the current mouse position.
    */
    const data::vec2& getMousePosition() const
    {
        return input.mouse.pos;
    }

    /****************************** Constructors ******************************/

    InputSystem(uint32_t* const windowWidth, uint32_t* const windowHeight);
};


#endif // SRC_INPUT_SYSTEM_H
