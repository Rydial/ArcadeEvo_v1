#include "GameEngine.h"

#include "Debug.h"
#include "ExitCodes.h"
#include "Renderers.h"

#include <SDL2/SDL.h>


////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// GAME ENGINE //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


void GameEngine::init()
{
    /************************* Engine Initialization **************************/

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

    /*********************** Post Engine Initialization ***********************/

    engineInitialized = true;

    debug::print("Main Engine Initialized");
}


void GameEngine::run()
{
    // Validate Engine Initialization
    if (!engineInitialized)
        return;

    /******************************* Main Loop ********************************/

    while (true)
    {
        /*********************** User Input Processing ************************/

        // Process Window Events
        if (renderer->pollEvents() == exitcode::EXIT_PROGRAM)
            break;

        // Process Keyboard Events
        // ...

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
    : renderer{std::make_unique<OpenGLRenderer>()}
{

}

/******************************** Destructors *********************************/

GameEngine::~GameEngine() = default;
