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

    struct CurrentInput
    {
        bool key[static_cast<uint8_t>(input::Key::COUNT)];

        struct Mouse
        {
            data::vec2 pos;
            bool       btns[static_cast<uint8_t>(input::Mouse::COUNT)];
        } mouse;


        bool&       operator[](input::Key type)
        {
            return key[static_cast<uint8_t>(type)];
        }
        const bool& operator[](input::Key type) const
        {
            return key[static_cast<uint8_t>(type)];
        }

        bool&       operator[](input::Mouse type)
        {
            return mouse.btns[static_cast<uint8_t>(type)];
        }
        const bool& operator[](input::Mouse type) const
        {
            return mouse.btns[static_cast<uint8_t>(type)];
        }
    };


    struct SavedInput
    {
        bool key  [static_cast<uint8_t>(input::Key  ::COUNT)];
        bool mouse[static_cast<uint8_t>(input::Mouse::COUNT)];

        bool&       operator[](input::Key type)
        {
            return key[static_cast<uint8_t>(type)];
        }
        const bool& operator[](input::Key type) const
        {
            return key[static_cast<uint8_t>(type)];
        }

        bool&       operator[](input::Mouse type)
        {
            return mouse[static_cast<uint8_t>(type)];
        }
        const bool& operator[](input::Mouse type) const
        {
            return mouse[static_cast<uint8_t>(type)];
        }
    
    };

    /****************************** Raw Pointers ******************************/

    uint32_t* const windowWidth  {};
    uint32_t* const windowHeight {};

    /******************************* Variables ********************************/

    CurrentInput current {};
    SavedInput   saved   {};

public:

    /***************************** Main Functions *****************************/

    void update();

    /******************************* Functions ********************************/

    /*
        Clicks the specified mouse input down.
    */
    void click(input::Mouse type) {saved[type] = true;}


    /*
        Returns whether the specified input is being clicked/pressed down.
    */
    bool isDown(input::Mouse type) const {return current[type];}
    bool isDown(input::Key   type) const {return current[type];}


    /*
        Presses the specified keyboard input down.
    */
    // void press(/* input::Key type */)
    // {

    // }


    /*
        Release the specified clicked/pressed down input.
    */
    void release(input::Mouse type) {saved[type] = false;}
    void release(input::Key /* type */)
    {
        
    }

    /*
        Returns whether the specified input was previously clicked/pressed down.
    */
    bool wasDown(input::Mouse type) const {return saved[type];}
    bool wasDown(input::Key   type) const {return saved[type];}

    /******************************** Getters *********************************/

    /*
        Returns a pair of references to the current mouse position.
    */
    const data::vec2& getMousePosition() const
    {
        return current.mouse.pos;
    }

    /****************************** Constructors ******************************/

    InputSystem(uint32_t* const windowWidth, uint32_t* const windowHeight);
};


#endif // SRC_INPUT_SYSTEM_H
