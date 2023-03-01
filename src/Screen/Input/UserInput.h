#ifndef SRC_USER_INPUT_H
#define SRC_USER_INPUT_H


#include <cstdint>


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// User Input //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


namespace input
{
    enum class Mouse : uint8_t
    {
        BUTTON_1              ,
        LEFT        = BUTTON_1,

        COUNT                 
    };


    enum class Key   : uint8_t
    {
        ENTER                 ,

        COUNT                 
    };


    enum class State : uint8_t
    {
        NONE                  ,
        CLICKED               ,
        PRESSED      = CLICKED,
        HELD                  ,
        RELEASED              ,

        COUNT
    };
}


#endif // SRC_USER_INPUT_H
