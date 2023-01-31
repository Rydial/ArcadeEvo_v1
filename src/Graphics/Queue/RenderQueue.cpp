#include "RenderQueue.h"


////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// Render Queue //////////////////////////////////
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


void RenderQueue::build(void* ptr, size_t maxCount, size_t typeSize)
{
    DEBUG_ASSERT(ptr != nullptr);

    data = ptr;
    this->maxCount = maxCount;
    this->typeSize = typeSize;

    // Reset Count
    count = 0;

    // Fill Data Pointer
    buildRenderQueue();
}
