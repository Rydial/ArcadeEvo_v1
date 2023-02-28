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

        COUNT                 ,

        LEFT = BUTTON_1       ,
    };


    enum class Key   : uint8_t
    {
        ENTER                 ,

        COUNT                 ,
    };


    enum class State : uint8_t
    {
        RELEASED              , // 0
        PRESSED               , // 1

        COUNT                 ,

        CLICKED = PRESSED     ,
    };

    /*
        Returns a unique value for the given input value and state pair.
    */
    constexpr inline uint32_t pair(Mouse type, State state)
    {
        return (static_cast<uint32_t>(type)                 *
                static_cast<uint32_t>(input::State::COUNT)) +
                static_cast<uint32_t>(state);
    }
    constexpr inline uint32_t pair(Key type, State state)
    {
        return (static_cast<uint32_t>(type)                 *
                static_cast<uint32_t>(input::State::COUNT)) +
                static_cast<uint32_t>(state)                +
                pair(input::Mouse::COUNT, input::State::RELEASED);
    }
}


#endif // SRC_USER_INPUT_H
