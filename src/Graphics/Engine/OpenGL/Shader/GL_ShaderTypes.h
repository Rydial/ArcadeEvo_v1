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


    struct quad
    {
        vec2 vPositions[4];
        vec2 vTexCoords[4];
        uint vTexIndex;
        uint unused;
    };
}


#endif // SRC_GL_SHADER_TYPES_H
