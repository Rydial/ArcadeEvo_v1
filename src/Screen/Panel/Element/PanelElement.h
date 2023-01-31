#ifndef SRC_PANEL_ELEMENT_H
#define SRC_PANEL_ELEMENT_H


#include <cstdint>


////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// Panel Element /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


class PanelElement
{
public:

    /******************************* Variables ********************************/

    float xPosition, yPosition;
    float width, height;

    /***************************** Main Functions *****************************/

    virtual uint32_t processUserInput() = 0;
};


#endif // SRC_PANEL_ELEMENT_H
