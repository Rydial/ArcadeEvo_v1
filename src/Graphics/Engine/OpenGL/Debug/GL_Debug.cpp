#include "GL_Debug.h"

#include <glad/glad.h>


////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// DEBUG /////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


void debug::opengl::checkError(std::string_view file, int line)
{
    // Iterate through Errors
    for (GLenum errorCode {}; (errorCode = glGetError()) != GL_NO_ERROR;)
    {
        // Identify Error
        switch (errorCode)
        {
            case GL_INVALID_ENUM:
                debug::throwError(
                    file, line,
                    "%", STRINGIFY(GL_INVALID_ENUM));
                break;
            case GL_INVALID_VALUE:
                debug::throwError(
                    file, line,
                    "%", STRINGIFY(GL_INVALID_VALUE));
                break;
            case GL_INVALID_OPERATION:
                debug::throwError(
                    file, line,
                    "%", STRINGIFY(GL_INVALID_OPERATION));
                break;
            case GL_STACK_OVERFLOW:
                debug::throwError(
                    file, line,
                    "%", STRINGIFY(GL_STACK_OVERFLOW));
                break;
            case GL_STACK_UNDERFLOW:
                debug::throwError(
                    file, line,
                    "%", STRINGIFY(GL_STACK_UNDERFLOW));
                break;
            case GL_OUT_OF_MEMORY:
                debug::throwError(
                    file, line,
                    "%", STRINGIFY(GL_OUT_OF_MEMORY));
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                debug::throwError(
                    file, line,
                    "%", STRINGIFY(GL_INVALID_FRAMEBUFFER_OPERATION));
                break;
        }
    }
}
