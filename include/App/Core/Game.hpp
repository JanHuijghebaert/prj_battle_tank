#ifndef __APP_CORE_GAME__HPP__
#define __APP_CORE_GAME__HPP__

#include "App/Core/Factory.hpp"

namespace App::Core {
class Game {
  public:
    Game(Factory* factory);

    int start();

  private:
    Factory* factory;
};
} // namespace App::Core

#endif
