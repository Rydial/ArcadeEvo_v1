#ifndef SRC_GAME_ENGINE_H
#define SRC_GAME_ENGINE_H


#include <memory>


////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// Game Engine //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


class GameEngine
{
private:

    /***************************** Smart Pointers *****************************/

    std::unique_ptr<class EntityComponentSystem> ecs {};
    std::unique_ptr<class RenderQueue> renderQueue {};
    std::unique_ptr<class RenderEngine> renderer {};
    std::unique_ptr<class ScreenManager> screenManager {};

    /******************************* Variables ********************************/

    bool engineInitialized {false};

public:

    /****************************** Constructors ******************************/

    GameEngine();

    /****************************** Destructors *******************************/

    ~GameEngine();

    /***************************** Main Functions *****************************/

    void init();
    void run();
    void cleanup();
};


#endif // SRC_GAME_ENGINE_H
