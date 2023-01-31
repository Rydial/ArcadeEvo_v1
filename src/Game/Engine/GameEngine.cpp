#include "GameEngine.h"

#include "Debug.h"
#include "EntityComponentSystem.h"
#include "ExitCodes.h"
#include "Renderers.h"
#include "RenderQueue.h"
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

        // Initialize Entity Component System
        ecs->init();

        // Initialize Screens
        screenManager->init();

        // Initialize Render Queue
        renderQueue->setBuilder([this] () {screenManager->fillRenderQueue();});                                                           
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

        // Update Current Screen
        screenManager->update();

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
    : ecs{std::make_unique<EntityComponentSystem>()},
      renderQueue{std::make_unique<RenderQueue>()},
      renderer{std::make_unique<GLRenderer>(renderQueue.get())},
      screenManager{std::make_unique<ScreenManager>(renderQueue.get())}
{

}

/******************************** Destructors *********************************/

GameEngine::~GameEngine() = default;
