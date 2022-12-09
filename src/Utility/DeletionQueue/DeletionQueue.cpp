#include "DeletionQueue.h"


////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// DELETION QUEUE ////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


void DeletionQueue::emplace(std::function<void()>&& func)
{
    queue.emplace(func);
}


void DeletionQueue::flush()
{
    // Iterate the Stack from Top to Bottom
    while (!queue.empty())
    {
        // Execute Stored Function
        queue.top()();

        // Remove Function
        queue.pop();
    }
}
