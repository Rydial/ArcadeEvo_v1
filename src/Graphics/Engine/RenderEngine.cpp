#include "RenderEngine.h"

#include "Debug.h"
#include "ExitCodes.h"

#include <SDL2/SDL.h>


////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// RENDER ENGINE /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


int RenderEngine::pollEvents()
{
    SDL_Event event {};

    // Extract Events from Queue
    while (SDL_PollEvent(&event))
    {                                                                     
        // Exit Game (Click 'X' or Alt + F4)
        if (event.type == SDL_QUIT)
            return exitcode::EXIT_PROGRAM;

        // Window Events
        else if (event.type == SDL_WINDOWEVENT)
        {
            // Window Resize
            if (event.window.event == SDL_WINDOWEVENT_RESIZED)
                setViewport(event.window.data1, event.window.data2);
        }
            
    }

    return exitcode::CONT_PROGRAM;
}
