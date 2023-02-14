#ifndef SRC_PANEL_ELEMENT_H
#define SRC_PANEL_ELEMENT_H


#include <functional>


////////////////////////////////////////////////////////////////////////////////
///////////////////////////// Forward Declarations /////////////////////////////
////////////////////////////////////////////////////////////////////////////////


enum class UserInput : uint32_t;


////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// Panel Element /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


class PanelElement
{
public:

    /******************************* Variables ********************************/

    // Functional Data
    std::function<void(const UserInput)> processInput {};

    // Styling Data
    float    xPosition {}, yPosition {};
    float    width     {}, height    {};
    uint32_t texIndex  {};

    /***************************** Main Functions *****************************/

    virtual void addTo(class RenderQueue* const renderQueue);

    /****************************** Destructors *******************************/

    virtual ~PanelElement() = default;
};


#endif // SRC_PANEL_ELEMENT_H
