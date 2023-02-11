#include "PanelElement.h"

#include "Debug.h"
#include "GL_ShaderTypes.h"
#include "RenderQueue.h"


////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// Panel Element /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


void PanelElement::addTo(RenderQueue* const renderQueue)
{
    DEBUG_ASSERT(renderQueue != nullptr);

    auto& quad {renderQueue->nextSlot<shader::opengl::quad>()};
    
    float vertices[] { // Temp
        -0.5f, -0.5f,      0.0f, 1.0f,      // Bottom Left
         0.5f, -0.5f,      1.0f, 1.0f,      // Bottom Right
         0.5f,  0.5f,      1.0f, 0.0f,      // Top Right
        -0.5f,  0.5f,      0.0f, 0.0f,      // Top Left
    };

    memcpy(quad.vertex, vertices, sizeof(vertices));
}
