#include "GameEngine.h"

#include "Debug.h"
#include "RenderEngine.h"

#include <SDL2/SDL.h>


////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// GAME ENGINE //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


void GameEngine::init()
{
    try
    {
        // Initialize Render Engine
        renderer->init();
    }
    catch (const std::runtime_error& e)
    {
        debug::printf("%\nTerminating Program.", e.what());
        return;
    }
    catch (...)
    {
        debug::print("Unknown Error Caught.\nTerminating Program.");
        return;
    }

    // Engine Initialization Success
    isRunning = true;
    debug::print("Main Engine Initialized");
}


void GameEngine::run()
{
    SDL_Event event {};

    /******************************* Main Loop ********************************/

    while (isRunning)
    {
        /*************************** SDL Event Poll ***************************/

        while (SDL_PollEvent(&event))
        {
            // Exit Game (Click 'X' or Alt + F4)
            if (event.type == SDL_QUIT)
                isRunning = false;
        }

        /************************* Graphics Rendering *************************/

        // Render Game Window and Graphics
        renderer->render();
    }
}


void GameEngine::cleanup()
{
    // Cleanup Render Engine
    renderer->cleanup(); 

    // Exit SDL2
    SDL_Quit();

    // Output Engine Cleanup Success
    debug::print("Main Engine Cleaned");
}

/******************************** Constructors ********************************/

GameEngine::GameEngine()
    : renderer{std::make_unique<RenderEngine>()}
{

}

/******************************** Destructors *********************************/

GameEngine::~GameEngine() = default;
