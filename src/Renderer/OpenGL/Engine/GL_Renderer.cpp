#include "GL_Renderer.h"

#include "GL_Debug.h"
#include "GL_ShaderTypes.h"
#include "GL_Utilities.h"

#include <glad/glad.h>
#include <SDL2/SDL.h>

#include <string>
#include <sstream>


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

    // Initialize Buffers
    initBuffers();

    // Initialize Shaders
    initShaders();

    // Output Engine Initialization Success
    DEBUG_PRINT("OpenGL Renderer Initialized");
}


void GLRenderer::render()
{
    // Clear Screen Color
    glClearColor(0.f, abs(sin(frameNumber / 120.f)), 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);

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

/**************************** Init Stage Functions ****************************/

void GLRenderer::initWindow()
{
    // Initialize SDL Video
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        throw std::runtime_error(debug::str(
            "Failed to initialize SDL Video: %",
            SDL_GetError()));
    }
        
    
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

    // Validate Window
    if (!window)
    {
        throw std::runtime_error(debug::str(
            "Failed to initialize SDL Window: %",
            SDL_GetError()));
    }
    deleteQueue.emplace([this] () {SDL_DestroyWindow(window);});

    // Create Window Context
    windowContext = SDL_GL_CreateContext(window);
    deleteQueue.emplace([this] () {SDL_GL_DeleteContext(windowContext);});
}


void GLRenderer::initCore()
{
    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress))
        throw std::runtime_error("Failed to initialize GLAD");

    // Validate Direct State Access Support
    if (!GLAD_GL_ARB_direct_state_access)
        throw std::runtime_error("Direct State Access not supported");
}


void GLRenderer::initBuffers()
{
     float vertices[] = {
      -1.0f, -1.0f, 0.0f,       1.0f, 0.0f, 0.0f, // Bottom Left
       1.0f, -1.0f, 0.0f,       0.0f, 1.0f, 0.0f, // Bottom Right
       0.0f, 1.0f, 0.0f,        0.0f, 0.0f, 1.0f  // Top
    };

    /********************************** VBO ***********************************/
    
    // Initialize Vertex Buffer Object (DSA)
    GL_CHECK(glCreateBuffers(1, &vbo));

    // Initialize Vertex Buffer Data Store
    GL_CHECK(glNamedBufferStorage(
        vbo,                        // Buffer Object
        sizeof(vertices),           // Data Store Size
        vertices,                   // Data
        GL_DYNAMIC_STORAGE_BIT));   // Flags (Enable Dynamic Data Update)

    /********************************** VAO ***********************************/
    
    // Initialize Vertex Array Object (DSA)
    GL_CHECK(glCreateVertexArrays(1, &vao));

    // Bind Vertex Buffer to VAO
    uint32_t vaoBindingPoint {0};
    GL_CHECK(glVertexArrayVertexBuffer(
      vao,                          // VAO
      vaoBindingPoint,              // VBO Binding Point in VAO
      vbo,                          // VBO (to bind to VAO)
      0,                            // VBO First Element Offset
      6 * sizeof(float)));          // VBO Stride (Size of Each Vertex)

    // Enable Generic Vertex Attribute Indexes
    uint32_t attribPos {0};
    uint32_t attribCol {1};
    GL_CHECK(glEnableVertexArrayAttrib(vao, attribPos));
    GL_CHECK(glEnableVertexArrayAttrib(vao, attribCol));

    // Specify VAO Data Format
    GL_CHECK(glVertexArrayAttribFormat(vao, attribPos, 3, GL_FLOAT, false, 0));
    GL_CHECK(glVertexArrayAttribFormat(
        vao,                        // VAO
        attribCol,                  // Vertex Attribute Index
        3,                          // Number of Values Per Vertex
        GL_FLOAT,                   // Value Type
        false,                      // Normalize Values
        3 * sizeof(float)));        // Offset

    // Bind Vertex Attributes to VAO Binding Point
    GL_CHECK(glVertexArrayAttribBinding(vao, attribPos, vaoBindingPoint));
    GL_CHECK(glVertexArrayAttribBinding(vao, attribCol, vaoBindingPoint));
}


void GLRenderer::initShaders()
{
    /************************* Shader Initialization **************************/

    namespace util = utilities::opengl;

    // Initialize Shader Objects
    uint32_t vertexShader {
            util::loadShader(
                GL_VERTEX_SHADER,
                "src/Renderer/OpenGL/Shader/4_6_main.vert")
    };
    uint32_t fragmentShader {
        util::loadShader(
            GL_FRAGMENT_SHADER,
            "src/Renderer/OpenGL/Shader/temp.frag")
    };

    /********************* Shader Program Initialization **********************/

    // Create Program Object
    shaderProgram = GL_CHECK(glCreateProgram());

    // Link Shaders to Program
    GL_CHECK(glAttachShader(shaderProgram, vertexShader));
    GL_CHECK(glAttachShader(shaderProgram, fragmentShader));
    GL_CHECK(glLinkProgram(shaderProgram));

    /*********************** Shader Program Validation ************************/

    // Retrieve Shader Program Link Status
    int programCompiled {};
    GL_CHECK(glGetProgramiv(shaderProgram, GL_LINK_STATUS, &programCompiled));

    // Validate Shader Program
    if (!programCompiled)
    {
        // Retrieve Info Log
        char infoLog[512] {};
        GL_CHECK(glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog));
        
        throw std::runtime_error(
            debug::str("Shader Program Failed to Link: %", infoLog));
    }

    /**************************************************************************/

    // Delete Shaders Objects
    GL_CHECK(glDeleteShader(vertexShader));
    GL_CHECK(glDeleteShader(fragmentShader));

    // Use Shader Program
    GL_CHECK(glUseProgram(shaderProgram));
}

/********************************* Functions **********************************/

void GLRenderer::setViewport(uint32_t width, uint32_t height)
{
    // Set Viewport to Specified Dimensions
    glViewport(0, 0, width, height);
}


void GLRenderer::setViewportToCurrentWindow()
{
    // Retrieve Current Window's Size
    int width {}, height {};
    SDL_GetWindowSize(window, &width, &height);

    // Set Viewport to Window Size
    setViewport(width, height);
}
