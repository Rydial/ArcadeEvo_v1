#include "ScreenManager.h"

#include "Debug.h"
#include "EntityComponentSystem.h"
#include "ExitCodes.h"
#include "ScreenCodes.h"
#include "SharedData.h"


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
    // Panel& panel {getCurrentScreenPanel()};

    /************************* User Input Processing **************************/

    // Process User Input for Current Screen
    // uint32_t retCode {panel.processUserInput()};

    // switch (retCode)
    // {
    //     case exitcode::EXIT_PROGRAM:        // Program Exit
    //         return exitcode::EXIT_PROGRAM;

    //     case exitcode::CONT_PROGRAM:        // No Action
    //         break;

    //     default:                            // Switch Screen
    //         setCurrentScreen(retCode);
    //         break;
    // }

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
