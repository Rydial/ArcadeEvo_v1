#include "Panel.h"

#include "ExitCodes.h"
#include "GL_ShaderTypes.h"
#include "PanelElements.h"
#include "RenderQueue.h"
#include "SDL_Debug.h"
#include "UserInputs.h"

#include <SDL2/SDL.h>


////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// Panel /////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


uint32_t Panel::processUserInput() /* Work In Progress */
{
    /****************************** Mouse Hover *******************************/

    // Get Mouse State
    int xPos {}, yPos {};
    SDL_GetMouseState(&xPos, &yPos);

    /*
        Retrieve Mouse Hovered Element

        Notes: Assumes there are NO overlapping elements when rendering.
    */
    for (uint32_t id {0}; const auto& element : elements)
    {
        float left {element.xPosition}, right {left + element.width};
        float top {element.yPosition}, bottom {top + element.height};

        // Validate Cursor and Element Intersection (AABB Intersection)
        if (xPos >= left && xPos <= right && yPos >= top && yPos <= bottom)
        {
            // Set Focus Element
            setFocusElement(id);
            break;
        }

        ++id;
    }

    /******************************** Keyboard ********************************/

    // Retrieve Keyboard State
    [[maybe_unused]] const auto* keys {SDL_GetKeyboardState(nullptr)};

    // Retrieve Keyboard Selected Element
    // if (keys[SDL_SCANCODE_H])
    // ...

    /************************ Focus Element User Input ************************/

    // Validate Focus Element
    if (hasFocusElement())
    {
        // Process Focus Element's User Inputs
        return getFocusElement().processUserInput();
    }
    else
        return exitcode::CONT_PROGRAM;
}


void Panel::update() /* Work In Progress */
{

}


void Panel::render() /* Work In Progress */
{
    float vertices[] { // Temp
        -0.5f, -0.5f,      0.0f, 1.0f,      // Bottom Left
         0.5f, -0.5f,      1.0f, 1.0f,      // Bottom Right
         0.5f,  0.5f,      1.0f, 0.0f,      // Top Right
        -0.5f,  0.5f,      0.0f, 0.0f,      // Top Left
    };

    auto& quad {renderQueue->nextSlot<shader::opengl::quad>()};

    memcpy(quad.vertex, vertices, sizeof(vertices));
}

/******************************** Constructors ********************************/

Panel::Panel(RenderQueue* const renderQueue)
    : renderQueue{renderQueue}
{
    DEBUG_ASSERT(renderQueue != nullptr);
}
