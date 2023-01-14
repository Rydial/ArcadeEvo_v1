#ifndef SRC_SDL_DEBUG_H
#define SRC_SDL_DEBUG_H


#include "Debug.h"

#include <string_view>


////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// MACROS ////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


#ifndef NDEBUG  // Debug Mode

    /*
        Notes: Only works with copy assignment, copy initialization and ;
    */
    #define SDL_CHECK(x)                                                       \
        (debug::sdl::clearError(), x);                                         \
        debug::sdl::checkError(__FILE__, __LINE__)

#else           // Release Mode

    #define SDL_CHECK(x)
    
#endif


////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// DEBUG /////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


namespace debug::sdl
{
    /*
        Throws an runtime error if an SDL error occured
    */
    void checkError(std::string_view file, int line);


    /*
        Clears the previous error msg
    */
    void clearError();
}


#endif // SRC_SDL_DEBUG_H
