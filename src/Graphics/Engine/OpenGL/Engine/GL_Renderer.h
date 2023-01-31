#ifndef SRC_GL_RENDERER_H
#define SRC_GL_RENDERER_H


#include "RenderEngine.h"


////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// GL Renderer //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


class GLRenderer : public RenderEngine
{
private:

    /******************************* Constants ********************************/

    static constexpr uint32_t MAX_QUADRANTS {10000};
    static constexpr uint32_t VERTICES_PER_QUAD {4};
    static constexpr uint32_t INDICES_PER_QUAD {6};

    /****************************** Raw Pointers ******************************/

    void* windowContext {};
    class RenderQueue* renderQueue {};

    /******************************* Variables ********************************/

    uint32_t quadBuffer {};
    uint32_t shaderProgram {};

    // Temp
    uint32_t ebo; // Index Buffer
    uint32_t vbo;
    uint32_t vao;
    uint32_t texture {};

    /************************** Init Stage Functions **************************/

    void initWindow();
    void initCore();
    void initBuffers();
    void initShaders();
    void initTextures();

    /******************************* Functions ********************************/

    /*
    
    */
    void setViewport(uint32_t width, uint32_t height) override;
    

    /*
    
    */
    void setViewportToCurrentWindow();

public:

    /***************************** Main Functions *****************************/

    void init() override;
    void render() override;
    void cleanup() override;

    /****************************** Constructors ******************************/

    GLRenderer(class RenderQueue* const renderQueue);
};


#endif // SRC_GL_RENDERER_H
