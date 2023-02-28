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

    quad.vertex[0].position = {xPos        , yPos - height, depth}; // BL
    quad.vertex[1].position = {xPos + width, yPos - height, depth}; // BR
    quad.vertex[2].position = {xPos + width, yPos         , depth}; // TR
    quad.vertex[3].position = {xPos        , yPos         , depth}; // TL

    quad.vertex[0].texCoord = {0.0f, 1.0f};                         // BL
    quad.vertex[1].texCoord = {1.0f, 1.0f};                         // BR
    quad.vertex[2].texCoord = {1.0f, 0.0f};                         // TR
    quad.vertex[3].texCoord = {0.0f, 0.0f};                         // TL
}
