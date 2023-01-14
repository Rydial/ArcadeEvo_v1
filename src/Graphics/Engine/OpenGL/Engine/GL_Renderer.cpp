#include "GL_Renderer.h"

#include "GL_Debug.h"
#include "GL_ShaderTypes.h"
#include "GL_Utilities.h"
#include "SDL_Debug.h"
#include "Util_Image.h"

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

    // Initialize Textures
    initTextures();

    // Output Engine Initialization Success
    DEBUG_PRINT("OpenGL Renderer Initialized");
}


void GLRenderer::render()
{
    // Clear Screen Color
    GL_CHECK(glClearColor(0.f, abs(sin(frameNumber / 120.f)), 0.f, 1.f));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));

    float vertices[] { // Temp
        -0.5f, -0.5f,      0.0f, 1.0f,      // Bottom Left
         0.5f, -0.5f,      1.0f, 1.0f,      // Bottom Right
         0.5f,  0.5f,      1.0f, 0.0f,      // Top Right
        -0.5f,  0.5f,      0.0f, 0.0f,      // Top Left
    };

    // Update Buffer Data
    GL_CHECK(glNamedBufferSubData(
        vbo,                                // Buffer
        0,                                  // Offset
        sizeof(vertices),                   // Size
        vertices));                         // Data

    // Bind VAO
    GL_CHECK(glBindVertexArray(vao));

    // Draw Indexed
    GL_CHECK(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, nullptr));

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
    SDL_CHECK(SDL_Init(SDL_INIT_VIDEO));

    // Set Window Attributes
    SDL_CHECK(SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1)); // Double Buffer
    SDL_CHECK(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4)); // v4.
    SDL_CHECK(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6)); //   .6
    SDL_CHECK(SDL_GL_SetAttribute(                          // Core
        SDL_GL_CONTEXT_PROFILE_MASK,
        SDL_GL_CONTEXT_PROFILE_CORE));       
#ifdef _APPLE_
    SDL_CHECK(SDL_GL_SetAttribute(                          // Forward-Compat
        SDL_GL_CONTEXT_FLAGS,
        SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG));
#endif

    // Create Window
    window = SDL_CHECK(SDL_CreateWindow(
        "ArcadeEvo",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        1280, // Temp
        720,  // Temp
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE));
    deleteQueue.emplace([this] () {SDL_CHECK(SDL_DestroyWindow(window));});
    

    // Create Window Context
    windowContext = SDL_CHECK(SDL_GL_CreateContext(window));
    deleteQueue.emplace([this] () {SDL_GL_DeleteContext(windowContext);});
}


void GLRenderer::initCore()
{
    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress))
        THROW_ERROR("Failed to initialize GLAD");
}


void GLRenderer::initBuffers()
{
    /***************************** Vertex Buffers *****************************/

    // Initialize Vertex Buffer Object (DSA)
    GL_CHECK(glCreateBuffers(1, &vbo));
    deleteQueue.emplace([this] () {GL_CHECK(glDeleteBuffers(1, &vbo));});

    // Initialize Vertex Buffer Data Store (Immutable)
    uint32_t vertexSize {sizeof(float) * 4}; // Pos (2) + Tex Coords (2)
    uint32_t maxVBOSize {vertexSize * VERTICES_PER_QUAD * MAX_QUADRANTS};
    GL_CHECK(glNamedBufferStorage(
        vbo,                                // Buffer Object
        maxVBOSize,                         // Data Store Size
        nullptr,                            // Data (Uninitialized)
        GL_DYNAMIC_STORAGE_BIT));           // Flags (Enable Dynamic Update)

    /************************* Element Array Buffers **************************/

    // Initialize Element Array Buffer Object (DSA)
    GL_CHECK(glCreateBuffers(1, &ebo));
    deleteQueue.emplace([this] () {GL_CHECK(glDeleteBuffers(1, &ebo));});

    // Initialize Element Array Buffer Data Store (Immutable)
    uint8_t indices[6] {0, 1, 2, 2, 3, 0};

    GL_CHECK(glNamedBufferStorage(
        ebo,                                // Buffer Object
        sizeof(indices),                    // Data Store Size
        indices,                            // Data
        GL_CLIENT_STORAGE_BIT));            // Flags (???)

    /************************** Vertex Array Objects **************************/

    // Initialize Vertex Array Object (DSA)
    GL_CHECK(glCreateVertexArrays(1, &vao));
    deleteQueue.emplace([this] () {GL_CHECK(glDeleteVertexArrays(1, &vao));});

    // Bind Vertex Buffer to VAO
    uint32_t vaoBindingPoint {0};
    GL_CHECK(glVertexArrayVertexBuffer(
      vao,                                  // VAO
      vaoBindingPoint,                      // VBO Binding Point in VAO
      vbo,                                  // VBO
      0,                                    // VBO First Element Offset
      vertexSize));                         // VBO Stride (Size of Each Vertex)

    // Enable Generic Vertex Attribute Indexes
    uint32_t attribPos {0};
    uint32_t attribTexCoord {1};
    GL_CHECK(glEnableVertexArrayAttrib(vao, attribPos));
    GL_CHECK(glEnableVertexArrayAttrib(vao, attribTexCoord));

    // Specify VAO Data Format
    GL_CHECK(glVertexArrayAttribFormat(vao, attribPos, 2, GL_FLOAT, false, 0));
    GL_CHECK(glVertexArrayAttribFormat(
        vao,                        // VAO
        attribTexCoord,             // Vertex Attribute Index
        2,                          // Number of Values Per Vertex
        GL_FLOAT,                   // Value Type
        false,                      // Normalize Values
        2 * sizeof(float)));        // Offset

    // Bind Vertex Attributes to VAO Binding Point
    GL_CHECK(glVertexArrayAttribBinding(vao, attribPos, vaoBindingPoint));
    GL_CHECK(glVertexArrayAttribBinding(vao, attribTexCoord, vaoBindingPoint));

    // Bind Element Array Buffer to VAO
    GL_CHECK(glVertexArrayElementBuffer(vao, ebo));
}


void GLRenderer::initShaders()
{
    /************************* Shader Initialization **************************/

    namespace util = utilities::opengl;

    // Initialize Shader Objects
    uint32_t vertexShader {
        util::loadShader(
            GL_VERTEX_SHADER,
            "src/Graphics/Engine/OpenGL/Shader/4_6_main.vert")
    };
    uint32_t fragmentShader {
        util::loadShader(
            GL_FRAGMENT_SHADER,
            "src/Graphics/Engine/OpenGL/Shader/4_6_main.frag")
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
        
        THROW_ERROR("Shader Program Failed to Link: %", infoLog);
    }

    /**************************************************************************/

    // Delete Shaders Objects
    GL_CHECK(glDeleteShader(vertexShader));
    GL_CHECK(glDeleteShader(fragmentShader));

    // Use Shader Program
    GL_CHECK(glUseProgram(shaderProgram));
}


void GLRenderer::initTextures()
{
    namespace util = utilities;
    
    // Load Image from File
    auto image {util::loadImage("res/temp.png")};

    // Validate Image
    // if (!image.has_value())
    // ...

    // Initialize Texture
    GL_CHECK(glCreateTextures(GL_TEXTURE_2D, 1, &texture));
    deleteQueue.emplace([this] () {GL_CHECK(glDeleteTextures(1, &texture));});

    // Specify Texture Filters
    // GL_CHECK(glTextureParameteri(texture, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    // GL_CHECK(glTextureParameteri(texture, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    // GL_CHECK(glTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    // GL_CHECK(glTextureParameteri(texture, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    
    // Allocate Memory for Texture
    GL_CHECK(glTextureStorage2D(
        texture,                    // Texture
        1,                          // Number of Levels
        GL_RGBA8,                   // Format
        image->width,               // Width
        image->height));            // Height

    // Upload Texture Data
    GL_CHECK(glTextureSubImage2D(
        texture,                    // Texture
        0,                          // Mipmap Level
        0,                          // xOffset
        0,                          // yOffset
        image->width,               // Width
        image->height,              // Height
        GL_RGBA,                    // Format
        GL_UNSIGNED_BYTE,           // Data Type
        image->pixels));            // Data

    // Bind Texture to Texture Unit
    GL_CHECK(glBindTextureUnit(0, texture));

    // Free Image Pixels
    util::freeImage(image.value());
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
