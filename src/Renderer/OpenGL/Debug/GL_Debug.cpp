#include "GL_Debug.h"

#include <glad/glad.h>


////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// DEBUG /////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


void debug::opengl::checkError(const char *file, int line)
{
    // Iterate through Errors
    for (GLenum errorCode {}; (errorCode = glGetError()) != GL_NO_ERROR;)
    {
        // Identify Error
        std::string error;

        switch (errorCode)
        {
            case GL_INVALID_ENUM:
                error = "INVALID_ENUM";
                break;
            case GL_INVALID_VALUE:
                error = "INVALID_VALUE";
                break;
            case GL_INVALID_OPERATION:
                error = "INVALID_OPERATION";
                break;
            case GL_STACK_OVERFLOW:
                error = "STACK_OVERFLOW";
                break;
            case GL_STACK_UNDERFLOW:
                error = "STACK_UNDERFLOW";
                break;
            case GL_OUT_OF_MEMORY:
                error = "OUT_OF_MEMORY";
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                error = "INVALID_FRAMEBUFFER_OPERATION";
                break;
        }

        // Throw Error
        throw std::runtime_error(debug::str("% | % (%)", error, file, line));
    }
}
