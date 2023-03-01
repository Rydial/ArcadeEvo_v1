#include "ScreenManager.h"

#include "ExitCodes.h"
#include "SharedData.h"


////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// Screen Manager ////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


void ScreenManager::init()
{
    // Initialize Shared Render Queue's Builder
    initRenderQueueBuilder();

    // Initialize Screens
    initScreens();

    // Set Focus Screen
    // setFocusScreen(screencode::MAINMENU);

    DEBUG_PRINT("Screens Initialized");
}


uint32_t ScreenManager::update() /* WIP */
{
    // Retrieve and Store User Input
    input.update();

    // Update Focus Element & Process User Input
    updateFocusElement();

    // Update Screen
    // ...

    DEBUG_PRINT("Focus Panel ID : %", getCurrentScreen().focusPanelID);

    return exitcode::CONT_PROGRAM;
}


void ScreenManager::cleanup()
{
    DEBUG_PRINT("Screen Manager Cleaned");
}

/*************************** Update-Stage Functions ***************************/

void ScreenManager::updateFocusElement()
{
    // Clear Focus Element ID
    focusElementID.reset();

    /****************************** Mouse Hover *******************************/

    const auto& mousePos {input.getMousePosition()};

    // Iterate Current Panel's Elements
    for (auto elementID : getCurrentPanel().elementIDs)
    {
        const auto& element {getElement(elementID)};
        float left {element.xPos}, right  {left + element.width };
        float top  {element.yPos}, bottom {top  - element.height};

        /*  
            Validate Cursor and Element Intersection (AABB Intersection)

            Note: Assumes no overlapping elements.
        */
        if (mousePos.x < left   || mousePos.x > right)
            continue;
        if (mousePos.y < bottom || mousePos.y > top  )
            continue;

        // Set Focus Element ID
        focusElementID = elementID;
        break;
    }

    /**************************************************************************/

    if (focusElementID.has_value())
    {
        // Send Input to Focus Element
        getElement(focusElementID.value()).input();
    }    
}

/******************************** Constructors ********************************/

ScreenManager::ScreenManager(
    SharedData* const sData,
    class EntityComponentSystem* const ecs)
  : 
    sData{sData},
    ecs{ecs},
    input{&sData->window.width, &sData->window.height}
{
    DEBUG_ASSERT(this->sData != nullptr);
    DEBUG_ASSERT(this->ecs != nullptr);
}
