#ifndef SRC_GL_UTILITIES_H
#define SRC_GL_UTILITIES_H


#include <string>


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// Utilities ///////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


namespace utilities::opengl
{
    /*
        Loads the specified shader, and return its ID.

        Errors:
            - Throws a runtime error if source code file fails to load.

        Warnings:
            - Should only be used during engine initialization.
    */
    uint32_t loadShader(uint32_t type, const std::string& srcCodePath);
}


#endif // SRC_GL_UTILITIES_H
