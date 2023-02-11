#ifndef SRC_RENDER_QUEUE_H
#define SRC_RENDER_QUEUE_H


#include "Debug.h"
#include "UID_Generator.h"

#include <functional>


////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// Render Queue /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


class RenderQueue
{
private:

    /******************************* Variables ********************************/

    std::function<void()> buildRenderQueue {};
    size_t count {};
    void* data {};
    UID dataType {};
    UID_Generator uidGenerator {};
    size_t maxCount {};        

public:

    /***************************** Main Functions *****************************/

    template <typename T>
    void build(void* ptr, size_t maxCount)
    {
        DEBUG_ASSERT(ptr != nullptr);

        data = ptr;
        this->maxCount = maxCount;
        dataType = uidGenerator.getUID<T>();

        // Reset Count
        count = 0;

        // Fill Data Pointer
        buildRenderQueue();
    }

    /******************************* Functions ********************************/

    /*
        Returns a reference to the next available slot in the queue, enclosed in
        the specified data type

        Notes: Assumes 'count' will never exceed 'maxCount'
    */
    template <typename T>
    T& nextSlot()
    {
        DEBUG_ASSERT(dataType == uidGenerator.getUID<T>());
        DEBUG_ASSERT(count < maxCount);

        return static_cast<T*>(data)[count++];
    }

    /******************************** Setters *********************************/

    /*
        Sets the builder to the given function.
    */
    void setBuilder(std::function<void()>&& func);

    /******************************** Getters *********************************/

    /*
        Returns the number of renderables 'T' added to the render queue.
    */
    size_t getCount() const {return count;}
};


#endif // SRC_RENDER_QUEUE_H
