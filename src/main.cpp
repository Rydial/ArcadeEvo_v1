#include "GameEngine.h"


int main()
{
    GameEngine engine {};

    /************************** Main Engine Process ***************************/

    engine.init();

    engine.run();

    engine.cleanup();

    /**************************************************************************/

    return 0; // Default Exit
}
