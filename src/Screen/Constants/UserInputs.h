#ifndef SRC_USER_INPUTS_H
#define SRC_USER_INPUTS_H


#include <cstdint>


////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// User Inputs //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


enum class UserInput : uint32_t
{
    /********************************* Mouse **********************************/

    MOUSE_1,
    MOUSE_2,
    MOUSE_3,

    MOUSE_LEFT      = MOUSE_1,
    MOUSE_RIGHT     = MOUSE_2,
    MOUSE_MIDDLE    = MOUSE_3,

    /******************************** Keyboard ********************************/

    KEY_LEFT,
    KEY_RIGHT,
    KEY_UP,
    KEY_DOWN
};


#endif // SRC_USER_INPUTS_H
