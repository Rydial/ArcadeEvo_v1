#include "SDL_Debug.h"

#include <SDL2/SDL.h>


////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// DEBUG /////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


void debug::sdl::checkError(std::string_view file, int line)
{
    // Retrieve SDL Error Message
    std::string_view errorMsg {SDL_GetError()};

    // Throw Error if Message is Empty
    if (!errorMsg.empty())
        debug::throwError(file, line, "SDL Error: %", errorMsg);
}


void debug::sdl::clearError()
{
    // Clear Last Set Error Message
    SDL_ClearError();
}
