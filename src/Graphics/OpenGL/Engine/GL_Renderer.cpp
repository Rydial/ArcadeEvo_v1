#include "GL_Renderer.h"

#include "GL_Debug.h"
#include "GL_ShaderTypes.h"
#include "SDL_Debug.h"
#include "SharedData.h"

#include <glad/glad.h>
#include <SDL2/SDL.h>


////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// GL Renderer //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


void GLRenderer::init()
{
    // Create Window
    initWindow();

    // Initialize Rendering Core
    initCore();

    // Set Viewport
    setViewportToCurrentWindow();

    // Initialize Shaders
    initShaders();

    // Initialize Buffers
    initBuffers();

    // Initialize Textures
    initTextures();

    // Output Engine Initialization Success
    DEBUG_PRINT("OpenGL Renderer Initialized");
}


void GLRenderer::render()
{
    // Clear Screen Color
    GL_CHECK(glClearColor(0.f, abs(sin(frameNumber / 360.f)), 0.f, 1.f));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    // Update Push Constant Uniform Buffer
    shader::opengl::pushconstant pushConstant {};
    pushConstant.positionScale.x = 1.f / (sData->window.width * 0.5f);
    pushConstant.positionScale.y = 1.f / (sData->window.height * 0.5f);
#ifdef __APPLE__
    GL_CHECK(glBufferSubData(
        GL_UNIFORM_BUFFER,          // Target
        0,                          // Offset
        sizeof(pushConstant),       // Size
        &pushConstant));            // Data
#else // DSA
    GL_CHECK(glNamedBufferSubData(
        ubo,                        // Buffer
        0,                          // Offset
        sizeof(pushConstant),       // Size
        &pushConstant));            // Data
#endif

    // Update Vertex Buffer
#ifdef __APPLE__
    void* dataPtr = GL_CHECK(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
    sData->renderQueue.build<shader::opengl::quad>(dataPtr, MAX_QUADRANTS);
    GL_CHECK(glUnmapBuffer(GL_ARRAY_BUFFER));
#else // DSA
    void* dataPtr = GL_CHECK(glMapNamedBuffer(vbo, GL_WRITE_ONLY));
    sData->renderQueue.build<shader::opengl::quad>(dataPtr, MAX_QUADRANTS);
    GL_CHECK(glUnmapNamedBuffer(vbo));
#endif

    // Bind VAO
    GL_CHECK(glBindVertexArray(vao));

    // Draw Indexed
    GL_CHECK(glDrawElements(
        GL_TRIANGLES,
        INDICES_PER_QUAD * sData->renderQueue.getCount(),
        GL_UNSIGNED_SHORT,
        nullptr));

    // Swap Framebuffer (Double Buffer)
    SDL_GL_SwapWindow(window);

    ++frameNumber;
}


void GLRenderer::cleanup()
{
    // Call Default Cleanup
    RenderEngine::cleanup();

    // Output Engine Cleanup Success
    DEBUG_PRINT("OpenGL Renderer Cleaned");
}

/********************************* Functions **********************************/

void GLRenderer::setViewport(uint32_t width, uint32_t height)
{
    // Set Viewport to Specified Dimensions
    GL_CHECK(glViewport(0, 0, width, height));
}


void GLRenderer::setViewportToCurrentWindow()
{
    // Retrieve Current Window's Size
    int width {}, height {};
    SDL_GetWindowSize(window, &width, &height);

    // Set Viewport to Window Size
    setViewport(width, height);
}

/******************************** Constructors ********************************/

GLRenderer::GLRenderer(SharedData* const sData)
    : sData{sData}
{
    DEBUG_ASSERT(this->sData != nullptr);
}
