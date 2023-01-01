#include "GL_Utilities.h"

#include "GL_Debug.h"

#include <glad/glad.h>

#include <fstream>


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// Utilities ///////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


uint32_t utilities::opengl::loadShader(
    uint32_t type,
    const std::string& srcCodePath)
{
    /********************** Shader Source Code Retrieval **********************/
    
    // Open Source Code File
    std::ifstream file {srcCodePath};

    // Validate File
    if (!file)
    {
        throw std::runtime_error(
            debug::str("Failed to load file: %", srcCodePath));
    }

    // Retrieve File Raw
    std::string srcCode {
        (std::istreambuf_iterator<char>(file)),
        (std::istreambuf_iterator<char>()    ) 
    };

    // Close Source Code File
    file.close();

    /************************* Shader Initialization **************************/

    // Create Shader Object
    uint32_t shader {GL_CHECK(glCreateShader(type))};

    // Attach Source Code to Shader
    const char* srcCodeData {srcCode.c_str()};
    GL_CHECK(glShaderSource(shader, 1, &srcCodeData, nullptr));

    // Compile Shader
    GL_CHECK(glCompileShader(shader));

    /*************************** Shader Validation ****************************/
    
    // Retrieve Shader Compile Status
    int shaderCompiled {};
    GL_CHECK(glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderCompiled));

    if(!shaderCompiled)
    {
        // Retrieve Info Log
        char infoLog[512] {};
        GL_CHECK(glGetShaderInfoLog(shader, 512, nullptr, infoLog));

        throw std::runtime_error(
            debug::str("OpenGL Shader Failed to Compile: %", infoLog));
    }

    /**************************************************************************/

    return shader;
}
    