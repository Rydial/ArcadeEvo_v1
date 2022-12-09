#ifndef SRC_RENDER_ENGINE_H
#define SRC_RENDER_ENGINE_H


#include "DeletionQueue.h"


////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// RENDER ENGINE /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


class RenderEngine
{
private:

    /****************************** DEBUG MACROS ******************************/

#ifdef NDEBUG
    const bool useValidationLayers {false};
#else
    const bool useValidationLayers {true};
#endif

    /****************************** Data Structs ******************************/

    struct Extent2D
    {
        uint32_t width, height;
    };

    /******************************* Variables ********************************/

    // Raw Pointers
    struct SDL_Window* window {};
    void* windowContext {};

    // Normal Variables
    DeletionQueue deleteQueue {};
    Extent2D windowExtent {1280, 720};

    /************************** Init Stage Functions **************************/

    void initWindow();
    void initCore();

public:

    /***************************** Main Functions *****************************/

    void init();
    void render();
    void cleanup();
};


#endif // SRC_RENDER_ENGINE_H
