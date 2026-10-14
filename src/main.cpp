
#include <iostream>
#include "App/Core/Factory.hpp"
#include "App/Core/Game.hpp"
#include "App/UI/SdlFactory.hpp"

using namespace App::Core;
using namespace App::UI;

int main(void) {
    Factory* factory = new SdlFactory();
    Game*    game    = new Game(factory);
    return game->start();
}
