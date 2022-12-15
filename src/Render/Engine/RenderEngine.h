#ifndef SRC_RENDER_ENGINE_H
#define SRC_RENDER_ENGINE_H


#include "DeletionQueue.h"

#include <cstdint> // Temp


////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// RENDER ENGINE /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


class RenderEngine
{
protected:

    /******************************* Variables ********************************/

    // Raw Pointers
    struct SDL_Window* window {};

    // Normal Variables
    DeletionQueue deleteQueue {};
    uint32_t frameNumber {0};

    /******************************* Functions ********************************/

    virtual void setViewport(uint32_t width, uint32_t height) = 0;

public:

    /***************************** Main Functions *****************************/

    virtual void init() = 0;
    int pollEvents();
    virtual void render() = 0;
    virtual void cleanup() {deleteQueue.flush();};

    /****************************** Destructors *******************************/

    virtual ~RenderEngine() = default;
};


#endif // SRC_RENDER_ENGINE_H
