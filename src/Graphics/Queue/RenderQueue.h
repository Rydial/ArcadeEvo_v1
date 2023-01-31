#ifndef SRC_RENDER_QUEUE_H
#define SRC_RENDER_QUEUE_H


#include "Debug.h"

#include <functional>


////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// Render Queue //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


class RenderQueue
{
private:

    /******************************* Variables ********************************/

    std::function<void()> buildRenderQueue {};
    size_t count {};
    void* data {};
    size_t maxCount {};        
    size_t typeSize {};

public:

    /***************************** Main Functions *****************************/

    void setBuilder(std::function<void()>&& func);
    void build(void* ptr, size_t maxCount, size_t typeSize);

    /******************************* Functions ********************************/

    /*
        Returns a reference to the next available slot in the queue, enclosed in
        the specified data type

        Notes: Assumes 'count' will never exceed 'maxCount'
    */
    template <typename T>
    T& nextSlot()
    {
        DEBUG_ASSERT(sizeof(T) == typeSize);
        DEBUG_ASSERT(count < maxCount);

        return static_cast<T*>(data)[count++];
    }

    /******************************** Getters *********************************/

    size_t getCount() const {return count;}
};


#endif // SRC_RENDER_QUEUE_H
