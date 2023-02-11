#include "ScreenManager.h"

#include "Debug.h"
#include "SharedData.h"


////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// Screen Manager ////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


/*************************** Console Init Functions ***************************/

void ScreenManager::initConsole() /* Work In Progress */
{
    // Allocate Memory For Panels (Prevents Reference Invalidation)
    // uint32_t panelCount {1};
    // panels.reserve(panels.size() + panelCount);

    /******************************* Main Panel *******************************/

    // Initialize Main Panel
    // [[maybe_unused]] auto& mainPanel {
    //     panels.emplace_back(std::make_unique<Panel>(renderQueue))};
    // size_t mainPanelID {panels.size() - 1};

    /********************************* Screen *********************************/

    // Initialize Screen
    // auto& screen {screens.emplace_back()};

    // Add Panel IDs
    // screen.panelIDs.emplace_back(mainPanelID);

    // Set Screen Focus Panel
    // screen.currentPanelID = mainPanelID;
}

/************************** MainMenu Init Functions ***************************/

void ScreenManager::initMainMenu() /* Work In Progress */
{
    // Initialize Screen
    auto& screen {screens.emplace_back()};

    /******************************* Main Panel *******************************/

    // Initialize Main Panel
    auto mainPanelID {initMainMenuMainPanel()};

    // Initialize Main Panel and Store ID in Screen
    screen.panelIDs.emplace_back(mainPanelID);

    // Set Screen Focus Panel
    screen.focusPanel = mainPanelID;

    /****************************** Other Panels ******************************/

    // screen.panelIDs.emplace_back(initMainMenuSingleplayerPanel());
    // screen.panelIDs.emplace_back(initMainMenuMultiplayerPanel());
    // screen.panelIDs.emplace_back(initMainMenuSettingsPanel());
}


ScreenManager::PanelID ScreenManager::initMainMenuMainPanel()
{
    /********************************* Panel **********************************/

    // Initialize Panel
    [[maybe_unused]] auto& panel {panels.emplace_back()};
    size_t panelID {panels.size() - 1};

    // Set Panel Style
    panel.xPosition = 0.0f;
    panel.yPosition = 0.0f;
    panel.width     = sData->windowWidth;
    panel.height    = sData->windowHeight;
    // panel.texIndex = ...;

    /************************** Single Player Button **************************/

    // Initialize Single Player Button Element
    auto& singleplayerBtn {elements.emplace_back()};
    size_t singleplayerBtnID {elements.size() - 1};

    // Set Button Style
    singleplayerBtn.xPosition = 0.0f;
    singleplayerBtn.yPosition = 0.0f;
    singleplayerBtn.width     = sData->windowWidth;
    singleplayerBtn.height    = sData->windowHeight;
    // singleplayerBtn.texIndex = ...;

    // Add Button Element to Panel
    panel.elementIDs.emplace_back(singleplayerBtnID);

    /************************** Multi Player Button ***************************/

    

    /**************************************************************************/

    return panelID;
}

/*************************** Pacman Init Functions ****************************/

void ScreenManager::initPacman() /* Work In Progress */
{

}
