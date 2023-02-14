#include "ScreenManager.h"

#include "Debug.h"
#include "EntityComponentSystem.h"
#include "ExitCodes.h"
#include "ScreenCodes.h"
#include "SharedData.h"

#include <SDL2/SDL.h>


////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// Screen Manager ////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


void ScreenManager::init()
{
    /*
        Notes: Order of Screen Initialization Must Follow ScreenCode Order
    */

    // Initialize Console Screen
    initConsole();

    // Initialize MainMenu Screen
    initMainMenu();

    // Initialize Pacman Screen
    initPacman();

    // Set Focus Screen
    // setFocusScreen(screencode::MAINMENU);

    DEBUG_PRINT("Screens Initialized");
}


uint32_t ScreenManager::update()
{
    // const Screen& currentScreen {getCurrentScreen()};
    // Panel& focusPanel {panels.at(focusScreen.focusPanel)};

    /****************************** Mouse Hover *******************************/

    // Get Mouse State
    int xPos {}, yPos {};
    SDL_GetMouseState(&xPos, &yPos);

    /*
        Retrieve Mouse Hovered Element
        Notes: Assumes there are NO overlapping elements when rendering.
    */
    // for (uint32_t id {0}; const auto& element : elements)
    // {
    //     float left {element.xPosition}, right {left + element.width};
    //     float top {element.yPosition}, bottom {top + element.height};

    //     // Validate Cursor and Element Intersection (AABB Intersection)
    //     if (xPos >= left && xPos <= right && yPos >= top && yPos <= bottom)
    //     {
    //         // Set Focus Element
    //         setFocusElement(id);
    //         break;
    //     }

    //     ++id;
    // }

    /******************************** Keyboard ********************************/

    // Retrieve Keyboard State
    // [[maybe_unused]] const auto* keys {SDL_GetKeyboardState(nullptr)};

    // Retrieve Keyboard Selected Element
    // if (keys[SDL_SCANCODE_H])
    // ...

    /************************ Focus Element User Input ************************/

    // Validate Focus Element

    /**************************** Screen Updating *****************************/

    // Update Current Screen
    // panel.update();

    /**************************************************************************/

    return exitcode::CONT_PROGRAM;
}


void ScreenManager::fillRenderQueue() /* Work In Progress */
{
    const Screen& focusScreen {getCurrentScreen()};

    /********************************** Temp **********************************/

    const Panel& focusPanel {panels.at(focusScreen.focusPanel)};

    // Iterate Focus Panel's Elements
    for (const auto& elementID : focusPanel.elementIDs)
    {
        auto& element {elements.at(elementID)};

        // Add Element to Render Queue
        element.addTo(&sData->renderQueue);
    }

    /**************************************************************************/

    // std::vector<std::pair<uint32_t, uint32_t>> space {};

    // // Iterate Current Screen's Panels
    // for (const auto& panelID : focusScreen.panelIDs)
    // {
        
    // }
}


void ScreenManager::cleanup()
{
    DEBUG_PRINT("Screens Cleaned");
}

/******************************** Constructors ********************************/

ScreenManager::ScreenManager(
    SharedData* const sData,
    EntityComponentSystem* const ecs)
  : 
    sData{sData},
    ecs{ecs}
{
    DEBUG_ASSERT(sData != nullptr);
    DEBUG_ASSERT(ecs != nullptr);
}
