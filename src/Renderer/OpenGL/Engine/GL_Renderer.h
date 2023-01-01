#ifndef SRC_GL_RENDERER_H
#define SRC_GL_RENDERER_H


#include "RenderEngine.h"


////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// GL Renderer //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


class GLRenderer : public RenderEngine
{
private:

    /******************************* Variables ********************************/

    // Raw Pointers
    void* windowContext {};

    // Normal Variables
    uint32_t quadBuffer {};
    uint32_t shaderProgram {};

    // TEmp
    unsigned int vbo;
    unsigned int vao;

    /************************** Init Stage Functions **************************/

    void initWindow();
    void initCore();
    void initShaders();
    void initBuffers();

    /******************************* Functions ********************************/

    void setViewport(uint32_t width, uint32_t height) override;
    void setViewportToCurrentWindow();

public:

    /***************************** Main Functions *****************************/

    void init() override;
    void render() override;
    void cleanup() override;
};


#endif // SRC_GL_RENDERER_H
