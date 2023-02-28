#include "ScreenManager.h"

#include "GL_ShaderTypes.h"
#include "SharedData.h"


////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// Screen Manager ////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void ScreenManager::initRenderQueueBuilder()
{
    // Initialize Render Queue Builder
    sData->renderQueue.setBuilder([this] () 
    {
        const Screen& focusScreen {getCurrentScreen()};

        // Iterate Screen's Panels
        for (auto panelID : focusScreen.panelIDs)
        {
            const Panel& panel {panels.at(panelID)};
            float xPos {panel.xPos}, yPos {panel.yPos}, depth {panel.depth};
            float width {panel.width}, height {panel.height};

            // Add Panel to Render Queue
            auto& quad {sData->renderQueue.nextSlot<shader::opengl::quad>()};

            quad.vertex[0].position = {xPos        , yPos - height, depth};
            quad.vertex[1].position = {xPos + width, yPos - height, depth};
            quad.vertex[2].position = {xPos + width, yPos         , depth};
            quad.vertex[3].position = {xPos        , yPos         , depth};

            quad.vertex[0].texCoord = {0.0f, 1.0f};                        
            quad.vertex[1].texCoord = {1.0f, 1.0f};                        
            quad.vertex[2].texCoord = {1.0f, 0.0f};                        
            quad.vertex[3].texCoord = {0.0f, 0.0f};                        

            // Iterate Panel's Elements
            for (auto elementID : panel.elementIDs)
            {
                // Add Element to Render Queue
                getElement(elementID).addTo(&sData->renderQueue);
            }
        }
    });  
}


void ScreenManager::initScreens()
{
    const auto&& newPanel {[this] ()
    {
        panels.emplace_back();
        return static_cast<ID>(panels.size() - 1);
    }};
    const auto&& newScreen {[this] ()
    {
        screens.emplace_back();
        return static_cast<ID>(screens.size() - 1);
    }};
    ScreenMap screenMap {
        {"MainMenu"             , newScreen()},
        {"MainMenu_Main"        , newPanel() },
        {"MainMenu_Singleplayer", newPanel() },
    };

    /*
        Assuming Screens, Panels, and Elements will remain fixed.
    */

    // Initialize Console Screen
    initConsole(screenMap);

    // Initialize MainMenu Screen
    initMainMenu(screenMap);

    // Initialize Pacman Screen
    initPacman(screenMap);
}

/*************************** Console Init Functions ***************************/

void ScreenManager::initConsole(const ScreenMap& /* screenMap */) /* WIP */
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

    // Set Screen Focus Panel ID
    // screen.currentPanelID = mainPanelID;
}

/************************** MainMenu Init Functions ***************************/

void ScreenManager::initMainMenu(const ScreenMap& screenMap) /* WIP */
{
    // Initialize Screen
    auto& screen {getScreen(screenMap.at("MainMenu"))};

    /******************************* Main Panel *******************************/

    // Initialize Main Panel
    auto mainPanelID {initMainMenuMainPanel(screenMap)};

    // Initialize Main Panel and Store ID in Screen
    screen.panelIDs.emplace_back(mainPanelID);

    // Set Screen Focus Panel ID
    screen.focusPanelID = mainPanelID;

    /****************************** Other Panels ******************************/

    // screen.panelIDs.emplace_back(initMainMenuSingleplayerPanel());
    // screen.panelIDs.emplace_back(initMainMenuMultiplayerPanel());
    // screen.panelIDs.emplace_back(initMainMenuSettingsPanel());
}


ScreenManager::PanelID ScreenManager::initMainMenuMainPanel(
    const ScreenMap& screenMap) /* WIP */
{
    /********************************* Panel **********************************/

    // Initialize Panel
    PanelID panelID {screenMap.at("MainMenu_Main")};
    auto&   panel   {getPanel(panelID)};

    // Set Panel Style
    panel.xPos      = -(sData->window.width  * 0.5f);
    panel.yPos      =   sData->window.height * 0.5f;
    panel.width     =   sData->window.width;
    panel.height    =   sData->window.height;
    panel.depth     = 0.1f;
    // panel.texIndex = ...;

    /************************** Single Player Button **************************/

    // Initialize Single Player Button Element
    auto&     singleplayerBtn   {elements.emplace_back()};
    ElementID singleplayerBtnID {static_cast<uint32_t>(elements.size()) - 1};

    // Set Button Style
    singleplayerBtn.xPos     = -(sData->window.width / 8.f);
    singleplayerBtn.yPos     = (sData->window.height / 8.f) + 150.f;
    singleplayerBtn.depth    = 0.f;
    singleplayerBtn.width    = sData->window.width / 4.f;
    singleplayerBtn.height   = sData->window.height / 4.f;
    // singleplayerBtn.texIndex = ...;

    // Set Button Input Processor
    PanelID singleplayerPanelID {screenMap.at("MainMenu_Singleplayer")};
    singleplayerBtn.input    = [=, this] (uint32_t type)
    {
        using namespace input;

        switch (type)
        {
            case pair(Mouse::LEFT, State::CLICKED):
                // Switch to Singleplayer Panel
                getCurrentScreen().focusPanelID = singleplayerPanelID;
                break;

            default: break;
        }
    };

    // Add Button Element to Panel
    panel.elementIDs.emplace_back(singleplayerBtnID);

    /************************** Multi Player Button ***************************/

    // Initialize Multi Player Button Element
    auto&     multiplayerBtn   {elements.emplace_back()};
    ElementID multiplayerBtnID {static_cast<uint32_t>(elements.size()) - 1};

    // Set Button Style
    multiplayerBtn.xPos     = -(sData->window.width / 8.f);
    multiplayerBtn.yPos     = (sData->window.height / 8.f) - 150.f;
    multiplayerBtn.depth    = 0.f;
    multiplayerBtn.width    = sData->window.width / 4.f;
    multiplayerBtn.height   = sData->window.height / 4.f;
    // multiplayerBtn.texIndex = ...;

    // Set Button Input Processor
    multiplayerBtn.input    = [] (uint32_t /* type */)
    {
        // DEBUG_PRINT("Input Process Called!");
    };

    // Add Button Element to Panel
    panel.elementIDs.emplace_back(multiplayerBtnID);

    /**************************************************************************/

    return panelID;
}

/*************************** Pacman Init Functions ****************************/

void ScreenManager::initPacman(const ScreenMap& /* screenMap */) /* WIP */
{

}
