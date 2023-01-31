#ifndef SRC_PANEL_H
#define SRC_PANEL_H


#include "PanelElement.h"

#include <optional>
#include <vector>


////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// Panel /////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


class Panel
{
private:

    /****************************** Raw Pointers ******************************/

    class RenderQueue* renderQueue {};

    /******************************* Variables ********************************/

    std::vector<PanelElement> elements {};
    std::optional<uint32_t> focusElementID {};

    /******************************* Functions ********************************/

    /*
        Returns if an element is being focused on (via UserInput)
    */
    bool hasFocusElement() {return focusElementID.has_value();}

    /******************************** Getters *********************************/

    /*
        Returns the element being focused on

        Notes: Use the function hasFocusElement() first to validate focus
        element existence.
    */
    PanelElement& getFocusElement()
    {
        return elements.at(focusElementID.value());
    }

    /******************************** Setters *********************************/

    /*
        Sets the focus element to the specified element ID
    */
    void setFocusElement(uint32_t id) {focusElementID = id;}

public:

    /***************************** Main Functions *****************************/

    virtual uint32_t processUserInput();
    virtual void update();
    virtual void render();

    /******************************* Functions ********************************/

    void addElement();

    /****************************** Constructors ******************************/

    Panel(class RenderQueue* const renderQueue);
};


#endif // SRC_PANEL_H
