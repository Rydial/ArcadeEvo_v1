#include "OpenGLRenderer.h"

#include "Debug.h"

#include <glad/glad.h>
#include <SDL2/SDL.h>


////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// OpenGL Renderer ////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


void OpenGLRenderer::init()
{
    // Create Window
    initWindow();

    // Initialize Rendering Core
    initCore();

    // Set Viewport
    int width {}, height {};
    SDL_GetWindowSize(window, &width, &height);
    setViewport(width, height);

    // Output Engine Initialization Success
    debug::print("Render Engine Initialized");
}


void OpenGLRenderer::render()
{
    // Clear Screen Color
    glClearColor(0.f, abs(sin(frameNumber / 120.f)), 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Swap Framebuffer (Double Buffer)
    SDL_GL_SwapWindow(window);

    ++frameNumber;
}


void OpenGLRenderer::cleanup()
{
    // Call Default Cleanup
    RenderEngine::cleanup();

    // Output Engine Cleanup Success
    debug::print("OpenGL Renderer Cleaned");
}

/**************************** Init Stage Functions ****************************/

void OpenGLRenderer::initWindow()
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
#ifdef _APPLE_
    SDL_GL_SetAttribute(                                    // Forward-Compat
        SDL_GL_CONTEXT_FLAGS,
        SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
#endif

    // Create Window
    window = SDL_CreateWindow(
        "ArcadeEvo",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        1280, // Temp
        720,  // Temp
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    deleteQueue.emplace([this] () {SDL_DestroyWindow(window);});

    // Create Window Context
    windowContext = SDL_GL_CreateContext(window);
    deleteQueue.emplace([this] () {SDL_GL_DeleteContext(windowContext);});
}


void OpenGLRenderer::initCore()
{
    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress))
        throw std::runtime_error("Failed to initialize GLAD");
}

/********************************* Functions **********************************/

void OpenGLRenderer::setViewport(uint32_t width, uint32_t height)
{
    glViewport(0, 0, width, height);
}
