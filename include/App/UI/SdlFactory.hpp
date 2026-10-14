#ifndef __APP_UI_SDLFACTORY__H__
#define __APP_UI_SDLFACTORY__H__

#include <iostream>
#include "App/Core/Factory.hpp"
#include "App/Core/Image.hpp"
#include "App/Core/PlayerCar.hpp"
#include "App/Core/Text.hpp"

using namespace App::Core;

namespace App::UI {
class SdlFactory : public Factory {
  public:
    SdlFactory();
    ~SdlFactory();

    bool init();
    bool show(std::string title, int screen_width, int screen_height);
    void clear();
    void update();
    void close();

    Key_t eventHandler();

    Image*     getNewImage(std::string path);
    Text*      getNewText(std::string path, int size, std::string text, int red, int green, int blue);
    PlayerCar* getNewPlayerCar(std::string path);
};
} // namespace App::UI

#endif
