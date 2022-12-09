#include "GameEngine.h"


int main()
{
    GameEngine engine {};

    /************************** Main Engine Process ***************************/

    engine.init();

    engine.run();

    engine.cleanup();

    /**************************************************************************/

    // Default Exit
    return 0;
}