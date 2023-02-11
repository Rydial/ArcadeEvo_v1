#ifndef SRC_SCREEN_MANAGER_H
#define SRC_SCREEN_MANAGER_H


#include "Debug.h"
#include "ECS_Enumerations.h"
#include "PanelElement.h"

#include <vector>

////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// Screen Manager ////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


class ScreenManager
{
private:

    /******************************** Aliases *********************************/

    using ID = uint32_t;

    using ElementID = ID;
    using PanelID = ID;
    using ScreenID = ID;

    /****************************** Data Structs ******************************/

    // Note: Screen Dimensions = Window Dimensions
    struct Screen
    {
        // Grouping Data
        std::vector<PanelID> panelIDs;
        PanelID focusPanel;
    };


    struct Panel
    {
        // Grouping Data
        std::vector<ElementID> elementIDs;
        ElementID focusElement;

        // Styling Data
        float    xPosition {}, yPosition {};
        float    width     {}, height    {};
        uint32_t texIndex  {};
    };

    /****************************** Raw Pointers ******************************/

    struct SharedData* sData {};
    class EntityComponentSystem* ecs {};

    /******************************* Variables ********************************/

    // bool consoleActive {false};
    ScreenID currentScreen {};
    std::vector<PanelElement> elements {};
    std::vector<Panel> panels {};
    std::vector<Screen> screens {};

    /************************** Init-Stage Functions **************************/

    void initConsole();
        PanelID initMainMenuMainPanel();
    void initMainMenu();
    void initPacman();

    /******************************** Getters *********************************/

    /*
        Returns a reference to the current screen.
    */
    Screen& getCurrentScreen()
    {
        DEBUG_ASSERT(currentScreen < screens.size());
        return screens.at(currentScreen);
    };

    /******************************** Setters *********************************/

    /*
        Sets the current screen to the given screen ID.
    */
    // void setCurrentScreen(uint32_t id) {currentScreenID = id;}

public:

    /***************************** Main Functions *****************************/

    void init();
    uint32_t update();
    void fillRenderQueue();
    void cleanup();

    /****************************** Constructors ******************************/

    ScreenManager(
        struct SharedData* const sData,
        class EntityComponentSystem* const ecs);
};


#endif // SRC_SCREEN_MANAGER_H
