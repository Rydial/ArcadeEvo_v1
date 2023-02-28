#include "GL_Renderer.h"

#include "GL_Debug.h"
#include "GL_ShaderTypes.h"
#include "GL_Utilities.h"
#include "SDL_Debug.h"
#include "SharedData.h"
#include "Util_Image.h"

#include <glad/glad.h>
#include <SDL2/SDL.h>

#include <climits>
#include <vector>


////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// GL Renderer //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


void GLRenderer::initWindow()
{
    // Initialize SDL Video
    SDL_CHECK(SDL_Init(SDL_INIT_VIDEO));

    // Set Window Attributes
    SDL_CHECK(SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1)); // Double Buffer
    SDL_CHECK(SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16));  // Depth Bit Size
    SDL_CHECK(SDL_GL_SetAttribute(                          // Core
        SDL_GL_CONTEXT_PROFILE_MASK,
        SDL_GL_CONTEXT_PROFILE_CORE));       
#ifdef __APPLE__
    SDL_CHECK(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4)); // v4.
    SDL_CHECK(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1)); //   .1
    SDL_CHECK(SDL_GL_SetAttribute(                          // Forward-Compat
        SDL_GL_CONTEXT_FLAGS,
        SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG));
#else
    SDL_CHECK(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4)); // v4.
    SDL_CHECK(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6)); //   .6
#endif

    // Create Window
    window = SDL_CHECK(SDL_CreateWindow(
        "ArcadeEvo",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        sData->window.width,
        sData->window.height,
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

    // Enable Depth Testing
    GL_CHECK(glEnable(GL_DEPTH_TEST));
    GL_CHECK(glDepthFunc(GL_LESS));     // Pass Values Less Than Current
}


void GLRenderer::initShaders()
{
    /************************* Shader Initialization **************************/

    namespace util = utilities::opengl;

    // Initialize Shader Objects
#ifdef __APPLE__
    uint32_t vertexShader {
        util::loadShader(
            GL_VERTEX_SHADER,
            "src/Graphics/Engine/OpenGL/Shader/3_3_main.vs")
    };
    uint32_t fragmentShader {
        util::loadShader(
            GL_FRAGMENT_SHADER,
            "src/Graphics/Engine/OpenGL/Shader/3_3_main.fs")
    };
#else
    uint32_t vertexShader {
        util::loadShader(
            GL_VERTEX_SHADER,
            "src/Graphics/OpenGL/Shader/4_6_main.vs")
    };
    uint32_t fragmentShader {
        util::loadShader(
            GL_FRAGMENT_SHADER,
            "src/Graphics/OpenGL/Shader/4_6_main.fs")
    };
#endif

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


void GLRenderer::initBuffers()
{
    /**************************** Uniform Buffers *****************************/

#ifdef __APPLE__
    // Set Shader Uniform Block 'PushConstant' to Binding Point '0'
    uint32_t pushConstantBindingIndex = GL_CHECK(glGetUniformBlockIndex(
        shaderProgram, "PushConstant"));   
    GL_CHECK(glUniformBlockBinding(shaderProgram, pushConstantBindingIndex, 0));
#endif

    // Initialize Uniform Buffer Object
#ifdef __APPLE__
    GL_CHECK(glGenBuffers(1, &ubo));
    GL_CHECK(glBindBuffer(GL_UNIFORM_BUFFER, ubo));
#else // DSA
    GL_CHECK(glCreateBuffers(1, &ubo));
#endif
    deleteQueue.emplace([this] () {GL_CHECK(glDeleteBuffers(1, &ubo));});

    // Initialize Uniform Buffer (Immutable)
#ifdef __APPLE__
    GL_CHECK(glBufferData(
        GL_UNIFORM_BUFFER,                  // Buffer Target
        sizeof(shader::opengl::pushconstant),   // Buffer Size
        nullptr,                            // Data (Uninitialized)
        GL_DYNAMIC_DRAW));                  // Flags (Enable Dynamic Update)
#else // DSA
    GL_CHECK(glNamedBufferStorage(
        ubo,                                // Buffer Object
        sizeof(shader::opengl::pushconstant),   // Buffer Size
        nullptr,                            // Data (Uninitialized)
        GL_DYNAMIC_STORAGE_BIT));           // Flags (Enable Dynamic Update)
#endif

    // Bind Uniform Block to Binding Point '0'
    GL_CHECK(glBindBufferBase(GL_UNIFORM_BUFFER, 0, ubo));

    /***************************** Vertex Buffers *****************************/

    // Initialize Vertex Buffer Object
#ifdef __APPLE__
    GL_CHECK(glGenBuffers(1, &vbo));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vbo));
#else // DSA
    GL_CHECK(glCreateBuffers(1, &vbo));
#endif
    deleteQueue.emplace([this] () {GL_CHECK(glDeleteBuffers(1, &vbo));});

    // Initialize Vertex Buffer (Immutable)
    size_t vertexSize {sizeof(shader::opengl::vert)};
    size_t maxVBOSize {vertexSize * VERTICES_PER_QUAD * MAX_QUADRANTS};
#ifdef __APPLE__
    GL_CHECK(glBufferData(
        GL_ARRAY_BUFFER,                    // Buffer Target
        maxVBOSize,                         // Buffer Size
        nullptr,                            // Data (Uninitialized)
        GL_DYNAMIC_DRAW));                  // Flags (Enable Dynamic Update)
#else // DSA
    GL_CHECK(glNamedBufferStorage(
        vbo,                                // Buffer Object
        maxVBOSize,                         // Buffer Size
        nullptr,                            // Data (Uninitialized)
        GL_MAP_WRITE_BIT));                 // Flags (Enable Map Write Access)
#endif

    /************************* Element Array Buffers **************************/

    // Initialize Element Array Buffer Object (DSA)
#ifdef __APPLE__
    GL_CHECK(glGenBuffers(1, &ebo));
    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));
#else // DSA
    GL_CHECK(glCreateBuffers(1, &ebo));
#endif
    deleteQueue.emplace([this] () {GL_CHECK(glDeleteBuffers(1, &ebo));});

    // Initialize Indices
    uint16_t indices[MAX_QUADRANTS * INDICES_PER_QUAD] {};
    DEBUG_ASSERT(MAX_QUADRANTS * INDICES_PER_QUAD < USHRT_MAX);

    for (size_t i {0}; i < MAX_QUADRANTS; ++i)
    {
        uint16_t* const ptr {indices + (i * INDICES_PER_QUAD)};
        ptr[0] = 0 + (VERTICES_PER_QUAD * i);
        ptr[1] = 1 + (VERTICES_PER_QUAD * i);
        ptr[2] = 2 + (VERTICES_PER_QUAD * i);
        ptr[3] = 2 + (VERTICES_PER_QUAD * i);
        ptr[4] = 3 + (VERTICES_PER_QUAD * i);
        ptr[5] = 0 + (VERTICES_PER_QUAD * i);
    }

    // Initialize Element Array Buffer (Immutable)
#ifdef __APPLE__
    GL_CHECK(glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        sizeof(indices),                    // Buffer Size
        indices,                            // Data
        GL_STATIC_READ));                   // Flags (Static & Read Only)
#else // DSA
    GL_CHECK(glNamedBufferStorage(
        ebo,                                // Buffer Object
        sizeof(indices),                    // Buffer Size
        indices,                            // Data
        GL_CLIENT_STORAGE_BIT));            // Flags (???)
#endif

/**************************** Vertex Array Objects ****************************/

    // Initialize Vertex Array Object (DSA)
#ifdef __APPLE__
    GL_CHECK(glGenVertexArrays(1, &vao));
    GL_CHECK(glBindVertexArray(vao));
#else // DSA
    GL_CHECK(glCreateVertexArrays(1, &vao));
#endif
    deleteQueue.emplace([this] () {GL_CHECK(glDeleteVertexArrays(1, &vao));});

    // Bind Vertex Buffer to VAO
#ifdef __APPLE__
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vbo));
#else // DSA
    uint32_t vaoBindingPoint {0};
    GL_CHECK(glVertexArrayVertexBuffer(
        vao,                                // VAO
        vaoBindingPoint,                    // VBO Binding Point in VAO
        vbo,                                // VBO
        0,                                  // VBO First Element Offset
        vertexSize));                       // Vertex Stride (Vertex Size)
#endif

    // Enable Generic Vertex Attribute Indexes
    uint32_t attribPos {0};
    uint32_t attribTexCoord {1};
#ifdef __APPLE__
    GL_CHECK(glEnableVertexAttribArray(attribPos));
    GL_CHECK(glEnableVertexAttribArray(attribTexCoord));
#else // DSA
    GL_CHECK(glEnableVertexArrayAttrib(vao, attribPos));
    GL_CHECK(glEnableVertexArrayAttrib(vao, attribTexCoord));
#endif

    // Specify Vertex Attribute Format
    std::vector<size_t> offsets {
        offsetof(shader::opengl::vert, position),
        offsetof(shader::opengl::vert, texCoord)
    };
#ifdef __APPLE__
    GL_CHECK(glVertexAttribPointer(
        0,                                  // Vertex Attribute Index
        3,                                  // Number of Values Per Vertex
        GL_FLOAT,                           // Value Type
        GL_FALSE,                           // Normalize Values
        vertexSize,                         // Vertex Stride (Vertex Size)
        (void*) offsets[0]));               // Vertex Attribute Offset
    GL_CHECK(glVertexAttribPointer(
        1,
        2,
        GL_FLOAT,
        GL_FALSE,
        vertexSize,
        (void*) offsets[1]));
#else // DSA
    GL_CHECK(glVertexArrayAttribFormat(
        vao,                                // VAO
        attribPos,                          // Vertex Attribute Index
        3,                                  // Number of Values Per Vertex
        GL_FLOAT,                           // Value Type
        GL_FALSE,                           // Normalize Values
        offsets[0]));                       // Offset
    GL_CHECK(glVertexArrayAttribFormat(
        vao,                
        attribTexCoord,     
        2,                  
        GL_FLOAT,           
        GL_FALSE,              
        offsets[1]));

    // Bind Vertex Attributes to VAO Binding Point
    GL_CHECK(glVertexArrayAttribBinding(vao, attribPos, vaoBindingPoint));
    GL_CHECK(glVertexArrayAttribBinding(vao, attribTexCoord, vaoBindingPoint));
#endif

#ifdef __APPLE__
    // Bind Element Array Buffer
    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));
#else // DSA
    // Bind Element Array Buffer to VAO
    GL_CHECK(glVertexArrayElementBuffer(vao, ebo));
#endif
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
#ifdef __APPLE__
    GL_CHECK(glGenTextures(1, &texture));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, texture));
#else // DSA
    GL_CHECK(glCreateTextures(GL_TEXTURE_2D, 1, &texture));
#endif
    deleteQueue.emplace([this] () {GL_CHECK(glDeleteTextures(1, &texture));});

    // Specify Texture Filters
    // GL_CHECK(glTextureParameteri(texture, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    // GL_CHECK(glTextureParameteri(texture, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    // GL_CHECK(glTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    // GL_CHECK(glTextureParameteri(texture, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    
    
#ifdef __APPLE__
    // Specify Texture Data & Format
    GL_CHECK(glTexImage2D(
        GL_TEXTURE_2D,              // Target
        0,                          // Mipmap Level
        GL_RGBA8,                   // Internal Format
        image->width,               // Width
        image->height,              // Height
        0,                          // Border ???
        GL_RGBA,                    // Format,
        GL_UNSIGNED_BYTE,           // Data Type
        image->pixels));            // Data
    
    // Generate Texture Mipmaps
    GL_CHECK(glGenerateMipmap(GL_TEXTURE_2D));
#else // DSA
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
#endif

    // Bind Texture to Texture Unit
#ifdef __APPLE__
    GL_CHECK(glActiveTexture(GL_TEXTURE0 + 0));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, texture));
#else // DSA
    GL_CHECK(glBindTextureUnit(0, texture));
#endif

    // Free Image Pixels
    util::freeImage(image.value());
}
