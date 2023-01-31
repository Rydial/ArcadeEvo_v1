#include "ScreenManager.h"

#include "Debug.h"
#include "ExitCodes.h"
#include "Panels.h"
#include "ScreenCodes.h"


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

    // Set Current Screen
    setCurrentScreen(screencode::MAINMENU);

    DEBUG_PRINT("Screens Initialized");
}


uint32_t ScreenManager::update()
{
    Panel& panel {getCurrentScreenPanel()};

    /************************* User Input Processing **************************/

    // Process User Input for Current Screen
    uint32_t retCode {panel.processUserInput()};

    switch (retCode)
    {
        case exitcode::EXIT_PROGRAM:        // Program Exit
            return exitcode::EXIT_PROGRAM;

        case exitcode::CONT_PROGRAM:        // No Action
            break;

        default:                            // Switch Screen
            setCurrentScreen(retCode);
            break;
    }

    /**************************** Screen Updating *****************************/

    // Update Current Screen
    panel.update();

    /**************************************************************************/

    return exitcode::CONT_PROGRAM;
}


void ScreenManager::fillRenderQueue() /* Work In Progress */
{
    // Fill Render Queue
    getCurrentScreenPanel().render();
    
    // if (consoleActive)
    // {
    //     // Retrieve Console Screen
    //     // ...

    //     // Render Console
    //     // ...
    // }
}


void ScreenManager::cleanup()
{
    DEBUG_PRINT("Screens Cleaned");
}

/**************************** Init-Stage Functions ****************************/

void ScreenManager::initConsole() /* Work In Progress */
{
    // Allocate Memory For Panels (Prevents Reference Invalidation)
    uint32_t panelCount {1};
    panels.reserve(panels.size() + panelCount);

    /******************************* Main Panel *******************************/

    // Initialize Main Panel
    [[maybe_unused]] auto& mainPanel {panels.emplace_back(renderQueue)};
    size_t mainPanelID {panels.size() - 1};

    /********************************* Screen *********************************/

    // Initialize Screen
    auto& screen {screens.emplace_back()};

    // Add Panel IDs
    screen.panelIDs.emplace_back(mainPanelID);

    // Set Screen Focus Panel
    screen.currentPanelID = mainPanelID;
}


void ScreenManager::initMainMenu() /* Work In Progress */
{
    // Allocate Memory For Panels (Prevents Reference Invalidation)
    uint32_t panelCount {1 /* + 3 */};
    panels.reserve(panels.size() + panelCount);

    /******************************* Main Panel *******************************/

    // Initialize Main Panel
    [[maybe_unused]] auto& mainPanel {panels.emplace_back(renderQueue)};
    size_t mainPanelID {panels.size() - 1};

    /*************************** Singleplayer Panel ***************************/

    // Initialize Singleplayer Panel
    // ...

    /*************************** Multiplayer Panel ****************************/

    // Initialize Multiplayer Panel
    // ...

    /***************************** Settings Panel *****************************/

    // Initialize Settings Panel
    // ...

    /********************************* Screen *********************************/

    // Initialize Screen
    auto& screen {screens.emplace_back()};

    // Add Panel IDs
    screen.panelIDs.emplace_back(mainPanelID);

    // Set Screen Focus Panel
    screen.currentPanelID = mainPanelID;
}


void ScreenManager::initPacman() /* Work In Progress */
{

}

/********************************** Getters ***********************************/

Panel& ScreenManager::getCurrentScreenPanel()
{
    DEBUG_ASSERT(currentScreenID >= 2);
    DEBUG_ASSERT(currentScreenID - 2 < screens.size());

    uint32_t index {screens.at(currentScreenID - 2).currentPanelID};
    return panels.at(index);
};

/******************************** Constructors ********************************/

ScreenManager::ScreenManager(class RenderQueue* const renderQueue)
    : renderQueue{renderQueue}
{
    DEBUG_ASSERT(renderQueue != nullptr);
}
