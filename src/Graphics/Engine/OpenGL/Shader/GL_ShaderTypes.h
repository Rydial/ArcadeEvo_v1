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


    struct vec3
    {
        float x, y, z;
    };


    struct vert
    {
        vec3 position;
        vec2 texCoord;
    };


    struct quad
    {
        vert vertex[4];
    };

    /************************** Named Shader Blocks ***************************/

    struct pushconstant
    {
        vec2 positionScale;
    };
}


#endif // SRC_GL_SHADER_TYPES_H
