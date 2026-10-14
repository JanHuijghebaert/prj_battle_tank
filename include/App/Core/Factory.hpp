#ifndef __APP_CORE_FACTORY__HPP__
#define __APP_CORE_FACTORY__HPP__

#include <iostream>
#include <string>
#include "App/Core/Image.hpp"
#include "App/Core/PlayerCar.hpp"
#include "App/Core/Text.hpp"

namespace App::Core {
class Factory {
  public:
    enum class Key_t {
        KEY_none,
        KEY_QUIT,
        KEY_P,
        KEY_Q,
        KEY_R,
        KEY_SPACE,
        KEY_UP_PRESSED,
        KEY_UP_RELEASED,
        KEY_DOWN_PRESSED,
        KEY_DOWN_RELEASED,
        KEY_LEFT_PRESSED,
        KEY_LEFT_RELEASED,
        KEY_RIGHT_PRESSED,
        KEY_RIGHT_RELEASED,
    };

    Factory();
    virtual ~Factory();

    virtual bool init()                                                       = 0;
    virtual bool show(std::string title, int screen_width, int screen_height) = 0;
    virtual void clear()                                                      = 0;
    virtual void update()                                                     = 0;
    virtual void close()                                                      = 0;

    virtual Key_t eventHandler() = 0;

    virtual Image*     getNewImage(std::string path)                                                          = 0;
    virtual Text*      getNewText(std::string path, int size, std::string text, int red, int green, int blue) = 0;
    virtual PlayerCar* getNewPlayerCar(std::string path)                                                      = 0;
};
} // namespace App::Core

#endif
