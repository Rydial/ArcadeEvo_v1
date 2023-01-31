#ifndef SRC_PANEL_BUTTON_H
#define SRC_PANEL_BUTTON_H


#include "PanelElement.h"

#include <functional>


////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// Panel Button /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace panel
{
    class Button : public PanelElement
    {
    public:

        /***************************** Variables ******************************/

        std::function<void()> onLeftClick;

        /*************************** Main Functions ***************************/

        uint32_t processUserInput() override;
    };
}




#endif // SRC_PANEL_BUTTON_H
