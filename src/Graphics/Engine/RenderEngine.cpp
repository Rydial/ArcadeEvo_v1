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
        switch (event.type)
        {
            case SDL_QUIT: // Exit Game (Click 'X' or Alt + F4)
                return exitcode::EXIT_PROGRAM;

            case SDL_WINDOWEVENT:

                // Window Resize
                if (event.window.event == SDL_WINDOWEVENT_RESIZED)
                    setViewport(event.window.data1, event.window.data2);

                break;

            default: break;
        } 
    }

    return exitcode::CONT_PROGRAM;
}
