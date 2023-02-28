#ifndef SRC_GL_SHADER_TYPES_H
#define SRC_GL_SHADER_TYPES_H


#include "DataStructs.h"


////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// SHADER ////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


namespace shader::opengl
{
    /******************************** Structs *********************************/
    
    struct vert
    {
        data::vec3 position;
        data::vec2 texCoord;
    };


    struct quad
    {
        vert vertex[4];
    };

    /************************** Named Shader Blocks ***************************/

    struct pushconstant
    {
        data::vec2 positionScale;
    };
}


#endif // SRC_GL_SHADER_TYPES_H
