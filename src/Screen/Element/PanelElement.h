#ifndef SRC_PANEL_ELEMENT_H
#define SRC_PANEL_ELEMENT_H


#include <cstdint>
#include <functional>


////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// Panel Element /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


class PanelElement
{
public:

    /******************************* Variables ********************************/

    // Functional Data
    std::function<void()> input {};

    // Styling Data
    float    xPos     {}, yPos   {}, depth {};
    float    width    {}, height {};
    uint32_t texIndex {};

    /***************************** Main Functions *****************************/

    virtual void addTo(class RenderQueue* const renderQueue);

    /****************************** Destructors *******************************/

    virtual ~PanelElement() = default;
};


#endif // SRC_PANEL_ELEMENT_H
