#ifndef SRC_SHARED_DATA_H
#define SRC_SHARED_DATA_H


#include "RenderQueue.h"


////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// Shared Data //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


struct SharedData
{
    RenderQueue renderQueue;
    struct Window {
        uint32_t width, height;
    } window;
};


#endif // SRC_SHARED_DATA_H