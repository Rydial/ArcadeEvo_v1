#ifndef SRC_OPENGL_RENDERER_H
#define SRC_OPENGL_RENDERER_H


#include "RenderEngine.h"


////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// OpenGL Renderer ////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


class OpenGLRenderer : public RenderEngine
{
private:

    /******************************* Variables ********************************/

    // Raw Pointers
    void* windowContext {};

    /************************** Init Stage Functions **************************/

    void initWindow();
    void initCore();

    /******************************* Functions ********************************/

    void setViewport(uint32_t width, uint32_t height) override;

public:

    /***************************** Main Functions *****************************/

    void init() override;
    void render() override;
    void cleanup() override;
};


#endif // SRC_OPENGL_RENDERER_H
