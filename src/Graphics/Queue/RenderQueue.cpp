#include "RenderQueue.h"


////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// Render Queue /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


void RenderQueue::setBuilder(std::function<void()>&& func)
{
    // Validate Queue Initialization
    if (buildRenderQueue != nullptr)
    {
        DEBUG_PRINT("RenderQueue already initialized.");
        return;
    }

    // Set Queue Builder
    buildRenderQueue = func;
}
