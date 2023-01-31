#ifndef SRC_SCREEN_MANAGER_H
#define SRC_SCREEN_MANAGER_H


#include "Panel.h"

#include <vector>


////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// Screen Manager ////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


class ScreenManager
{
private:

    /****************************** Data Structs ******************************/

    struct Screen
    {
        std::vector<uint32_t> panelIDs; // ID represents Panel Vector Index
        uint32_t currentPanelID;
    };

    /****************************** Raw Pointers ******************************/

    class RenderQueue* renderQueue {};

    /******************************* Variables ********************************/

    bool consoleActive {false};
    uint32_t currentScreenID {};    // ID represents Screen Code
    std::vector<Panel> panels {};
    std::vector<Screen> screens {};

    /************************** Init-Stage Functions **************************/

    void initConsole();
    void initMainMenu();
    void initPacman();

    /******************************** Getters *********************************/

    /*
        Return the focus panel for the current screen
    */
    Panel& getCurrentScreenPanel();

    /******************************** Setters *********************************/

    /*
        Set the current screen to the specified screen ID
    */
    void setCurrentScreen(uint32_t id) {currentScreenID = id;}

public:

    /***************************** Main Functions *****************************/

    void init();
    uint32_t update();
    void fillRenderQueue();
    void cleanup();

    /****************************** Constructors ******************************/

    ScreenManager(class RenderQueue* const renderQueue);
};


#endif // SRC_SCREEN_MANAGER_H
