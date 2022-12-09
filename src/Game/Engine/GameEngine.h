#ifndef SRC_GAME_ENGINE_H
#define SRC_GAME_ENGINE_H


#include <memory>


////////////////////////////////////////////////////////////////////////////////
///////////////////////////// FORWARD DECLARATIONS /////////////////////////////
////////////////////////////////////////////////////////////////////////////////


// class GameTimer;
class RenderEngine;
// class ScreenManager;


////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// GAME ENGINE //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


class GameEngine
{
private:

    /******************************* Variables ********************************/

    // std::unique_ptr<GameTimer> gameTimer {};
    bool isRunning {false};
    std::unique_ptr<RenderEngine> renderer {};
    // std::unique_ptr<ScreenManager> screenManager {};

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
