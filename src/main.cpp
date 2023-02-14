// #include "GameEngine.h"


// int main()
// {
//     GameEngine engine {};

//     /************************** Main Engine Process ***************************/

//     engine.init();

//     engine.run();

//     engine.cleanup();

//     /**************************************************************************/

//     return 0; // Default Exit
// }


#include "GL_Debug.h"
#include "GL_Utilities.h"
#include "SDL_Debug.h"
#include "Util_Image.h"

#include <glad/glad.h>
#include <SDL2/SDL.h>


// static constexpr uint32_t MAX_QUADRANTS {10000};
// static constexpr uint32_t VERTICES_PER_QUAD {4};
// static constexpr uint32_t INDICES_PER_QUAD {6};


int main()
{
    [[maybe_unused]] void* windowContext {};
    struct SDL_Window* window {};

    /******************************* Variables ********************************/

    // Temp
    uint32_t shaderProgram {};
    uint32_t ebo {};               // Index Buffer
    uint32_t vbo {};               // Vertex Buffer
    uint32_t vao {};               // Vertex Array
    // uint32_t ubo {};               // Uniform Buffer
    // uint32_t texture {};



    // Initialize SDL Video
    SDL_CHECK(SDL_Init(SDL_INIT_VIDEO));

    // Set Window Attributes
    SDL_CHECK(SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1)); // Double Buffer
    SDL_CHECK(SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32));  // Depth Bit Size
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
        1280,
        720,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE));
    

    // Create Window Context
    windowContext = SDL_CHECK(SDL_GL_CreateContext(window));

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress))
        THROW_ERROR("Failed to initialize GLAD");


    
    /************************* Shader Initialization **************************/

    namespace util = utilities::opengl;

    // Initialize Shader Objects
#ifdef __APPLE__
    uint32_t vertexShader {
        util::loadShader(
            GL_VERTEX_SHADER,
            "src/Graphics/Engine/OpenGL/Shader/temp.vs")
    };
    uint32_t fragmentShader {
        util::loadShader(
            GL_FRAGMENT_SHADER,
            "src/Graphics/Engine/OpenGL/Shader/temp.fs")
    };
#else
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







    // ------------------------------------------------------------------
    float vertices[] = {
        // positions         // texture coords
        -0.225f,  0.15f, 0.0f,  0.0f, 1.0f, // bottom left
         0.225f,  0.15f, 0.0f,  1.0f, 1.0f, // bottom right
         0.225f,  0.45f, 0.0f,  1.0f, 0.0f, // top right
        -0.225f,  0.45f, 0.0f,  0.0f, 0.0f, // top left

        -0.225f, -0.15f, 0.0f,  0.0f, 1.0f, // bottom left
         0.225f, -0.15f, 0.0f,  1.0f, 1.0f, // bottom right
         0.225f, -0.45f, 0.0f,  1.0f, 0.0f, // top right
        -0.225f, -0.45f, 0.0f,  0.0f, 0.0f  // top left
    };
    uint32_t indices[12] {0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4};
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    DEBUG_PRINT("VBO Size: %", sizeof(vertices));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // load and create a texture 
    // -------------------------
    unsigned int texture1, texture2;
    // texture 1
    // ---------
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1); 
     // set the texture wrapping parameters
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // // set texture filtering parameters
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    auto image {utilities::loadImage("res/temp.png")};
    if (image.has_value())
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->width, image->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    utilities::freeImage(image.value());
    // texture 2
    // ---------
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // set the texture wrapping parameters
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // // set texture filtering parameters
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    auto image2 {utilities::loadImage("res/wolf.png")};
    if (image2.has_value())
    {
        // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image2->width, image2->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image2->pixels);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    utilities::freeImage(image2.value());

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    GL_CHECK(glUseProgram(shaderProgram));
    // either set it manually like so:
    glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
    // or set it via the texture class
    glUniform1i(glGetUniformLocation(shaderProgram, "texture2"), 1);


    SDL_Event event {};

    while (true)
    {
        // Extract Events from Queue
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                return 0;
        }

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        // render container
        GL_CHECK(glUseProgram(shaderProgram));
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

        // Swap Framebuffer (Double Buffer)
        SDL_GL_SwapWindow(window);
    }


    return 0;
}

