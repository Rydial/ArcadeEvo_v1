#ifndef SRC_DELETION_QUEUE_H
#define SRC_DELETION_QUEUE_H


#include <functional>
#include <stack>


////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// DELETION QUEUE ////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


class DeletionQueue
{
private:

    /******************************* Variables ********************************/

    std::stack<std::function<void()>> queue {};

public:

    /***************************** Main Functions *****************************/

    void emplace(std::function<void()>&& func);
    void flush();
};


#endif // SRC_DELETION_QUEUE_H
