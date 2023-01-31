#ifndef SRC_GL_SHADER_TYPES_H
#define SRC_GL_SHADER_TYPES_H


////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// SHADER ////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


namespace shader::opengl
{
    /******************************** Structs *********************************/
    
    struct vec2
    {
        float x, y;
    };


    struct vert
    {
        vec2 position;
        vec2 texCoord;
    };


    struct quad
    {
        vert vertex[4];
    };
}


#endif // SRC_GL_SHADER_TYPES_H
