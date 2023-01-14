#include "GameEngine.h"

#include "Debug.h"
#include "ExitCodes.h"
#include "Renderers.h"
#include "ScreenManager.h"

#include <SDL2/SDL.h>


////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// Game Engine //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


void GameEngine::init()
{
    /************************* Engine Initialization **************************/

    try                                                                       
    {                                                                         
        // Initialize Render Engine
        renderer->init();

        // Initialize Screens
        screenManager->init();                                                             
    }

    // Catch Runtime Errors (Expected Errors)
    catch (const std::runtime_error& e)                                       
    {                                                                         
        DEBUG_PRINT(e.what());                     
        return;                                                                 
    }     

    // Catch Unexpected Errors
    catch (...)
    {
        DEBUG_PRINT("!Unknown Error Caught!");
        return;
    }

    /*********************** Post Engine Initialization ***********************/

    engineInitialized = true;

    DEBUG_PRINT("Game Engine Initialized");
}


void GameEngine::run()
{
    // Validate Engine Initialization
    if (!engineInitialized)
    {
        DEBUG_PRINT("Engine not initialized. Cannot run program.");
        return;
    }

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

        try                                                                       
        {                                                                         
            // Render Game Window and Graphics
            renderer->render();                                                              
        }

        // Catch Runtime Errors (Expected Errors)
        catch (const std::runtime_error& e)                                       
        {                                                                         
            DEBUG_PRINT("%\nTerminating Program.", e.what());                     
            return;                                                                 
        }     

        // Catch Unexpected Errors
        catch (...)
        {
            DEBUG_PRINT("Unknown Error Caught.\nTerminating Program.");
            return;
        }
    }
}


void GameEngine::cleanup()
{
    // Cleanup Screens
    screenManager->cleanup();

    // Cleanup Render Engine
    renderer->cleanup(); 

    // Exit SDL2
    SDL_Quit();

    // Output Engine Cleanup Success
    DEBUG_PRINT("Main Engine Cleaned");
}

/******************************** Constructors ********************************/

GameEngine::GameEngine()
    : renderer{std::make_unique<GLRenderer>()},
      screenManager{std::make_unique<ScreenManager>()}
{

}

/******************************** Destructors *********************************/

GameEngine::~GameEngine() = default;
