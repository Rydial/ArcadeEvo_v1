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

    //                |              Position               |  | TexCoord |
    quad.vertex[0] = {{xPosition - width, yPosition - height, 0.f}, {0.0f, 1.0f}}; // BL
    quad.vertex[1] = {{xPosition        , yPosition - height, 0.f}, {1.0f, 1.0f}}; // BR
    quad.vertex[2] = {{xPosition        , yPosition         , 0.f}, {1.0f, 0.0f}}; // TR
    quad.vertex[3] = {{xPosition - width, yPosition         , 0.f}, {0.0f, 0.0f}}; // TL
}
