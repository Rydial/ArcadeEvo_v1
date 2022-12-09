#include "RenderEngine.h"

#include "Debug.h"

#include <glad/glad.h>
#include <SDL2/SDL.h>


////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// RENDER ENGINE /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


void RenderEngine::init()
{
    // Create Window
    initWindow();

    // Output Engine Initialization Success
    debug::print("Render Engine Initialized");
}


void RenderEngine::render()
{
    
}


void RenderEngine::cleanup()
{
    // Cleanup Engine
    deleteQueue.flush();

    // Output Engine Cleanup Success
    debug::print("Render Engine Cleaned");
}

/************************** Init Stage Functions **************************/


void RenderEngine::initWindow()
{
    // Initialize SDL Video
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        throw std::runtime_error("Failed to initialize SDL Video.");
    
    // Set Window Attributes
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);            // Double Buffer
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);   // Version 4
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);   // Version  .6
    SDL_GL_SetAttribute(                                    // Core
        SDL_GL_CONTEXT_PROFILE_MASK,
        SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(                                    // Forward-Compat
        SDL_GL_CONTEXT_FLAGS,
        SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);

    // Create SDL Window
    window = SDL_CreateWindow(
        "ArcadeEvo",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        windowExtent.width,
        windowExtent.height,
        SDL_WINDOW_OPENGL);
    deleteQueue.emplace([this] () {SDL_DestroyWindow(window);});

    // Create Window Context
    windowContext = SDL_GL_CreateContext(window);
    deleteQueue.emplace([this] () {SDL_GL_DeleteContext(windowContext);});
}
