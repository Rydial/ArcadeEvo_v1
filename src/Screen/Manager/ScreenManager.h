#ifndef SRC_SCREEN_MANAGER_H
#define SRC_SCREEN_MANAGER_H


#include "Debug.h"
#include "ECS_Enumerations.h"
#include "InputSystem.h"
#include "PanelElement.h"

#include <optional>
#include <unordered_map>
#include <vector>

////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// Screen Manager ////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


class ScreenManager
{
private:

    /******************************** Aliases *********************************/

    using ID        = uint32_t;

    using PanelID   = ID;
    using ScreenID  = ID;
    using ElementID = ID;

    using ScreenMap = std::unordered_map<std::string, ID>;

    /****************************** Data Structs ******************************/

    struct Panel
    {
        // Grouping Data
        std::vector<ElementID> elementIDs;

        // Styling Data
        float    xPos     {}, yPos   {}, depth {};
        float    width    {}, height {};
        uint32_t texIndex {};
    };


    // Note: Screen Dimensions = Window Dimensions
    struct Screen
    {
        // Grouping Data
        std::vector<PanelID> panelIDs;
        PanelID focusPanelID;
    };

    /****************************** Raw Pointers ******************************/

    struct SharedData*            const sData {};
    class  EntityComponentSystem* const ecs   {};

    /**************************** Array Variables *****************************/

    std::vector<PanelElement> elements             {};
    std::vector<Panel>        panels               {};
    std::vector<Screen>       screens              {};

    /******************************* Variables ********************************/

    // bool consoleActive {false};
    ScreenID                 focusScreenID   {};
    std::optional<ElementID> focusElementID  {};
    InputSystem              input             ;

    /************************** Init-Stage Functions **************************/

    void initRenderQueueBuilder();
    void initScreens();
        void initConsole(const ScreenMap& screenMap);
        void initMainMenu(const ScreenMap& screenMap);
            PanelID initMainMenuMainPanel(const ScreenMap& screenMap);
        void initPacman(const ScreenMap& screenMap);

    /************************* Update-Stage Functions *************************/

    void updateFocusElement();

    /******************************** Getters *********************************/

    /*
        Returns a reference to the current screen.
    */
    Screen& getCurrentScreen()
    {
        DEBUG_ASSERT(focusScreenID < screens.size());
        return screens.at(focusScreenID);
    };


    /*
        Returns a reference to the current screen's focus panel.
    */
    Panel& getCurrentPanel()
    {
        DEBUG_ASSERT(getCurrentScreen().focusPanelID < panels.size());
        return panels.at(getCurrentScreen().focusPanelID);
    }


    /*
        Returns a reference to the specified element.
    */
    PanelElement& getElement(ElementID id)
    {
        DEBUG_ASSERT(id < elements.size());
        return elements.at(id);
    }


    /*
        Returns a reference to the specified panel.
    */
    Panel& getPanel(PanelID id)
    {
        DEBUG_ASSERT(id < panels.size());
        return panels.at(id);
    }


    /*
        Returns a reference to the specified screen.
    */
    Screen& getScreen(ScreenID id)
    {
        DEBUG_ASSERT(id < screens.size());
        return screens.at(id);
    }

    /******************************** Setters *********************************/

    /*
        Sets the current screen to the given screen ID.
    */
    // void setCurrentScreen(uint32_t id) {currentScreenID = id;}

public:

    /***************************** Main Functions *****************************/

    void     init();
    uint32_t update();
    void     cleanup();

    /****************************** Constructors ******************************/

    ScreenManager(
        struct SharedData* const sData,
        class EntityComponentSystem* const ecs);
};


#endif // SRC_SCREEN_MANAGER_H
