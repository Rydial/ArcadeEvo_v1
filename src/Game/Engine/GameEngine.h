#ifndef SRC_GAME_ENGINE_H
#define SRC_GAME_ENGINE_H


#include <memory>


////////////////////////////////////////////////////////////////////////////////
///////////////////////////// Forward Declarations /////////////////////////////
////////////////////////////////////////////////////////////////////////////////


// class GameTimer;
class RenderEngine;
class ScreenManager;


////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// Game Engine //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


class GameEngine
{
private:

    /******************************* Variables ********************************/

    // Smart Pointers
    // std::unique_ptr<GameTimer> gameTimer {};
    std::unique_ptr<RenderEngine> renderer {};
    std::unique_ptr<ScreenManager> screenManager {};

    // Normal Variables
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
