
#ifndef __APP_UI_SDLPLAYERCAR__HPP__
#define __APP_UI_SDLPLAYERCAR__HPP__

#include "App/Core/PlayerCar.hpp"
#include "App/UI/SdlTexture.hpp"
#include <SDL2/SDL.h>
#include <iostream>

using namespace App::Core;

namespace App::UI {
class SdlPlayerCar : public PlayerCar {
  public:
    /**
     * @brief Constructor
     * @param path Location of image file
     * @param gRenderer SDL renderer
     */
    SdlPlayerCar(std::string path, SDL_Renderer* gRenderer);
    ~SdlPlayerCar();

    /**
     * @brief Get texture width
     * @return Texture width
     */
    int getWidth();

    /**
     * @brief Get texture height
     * @return Texture height
     */
    int getHeight();

    /**
     * @brief Visualize player car
     */
    void visualize();

  private:
    SdlTexture    thisTexture;
    SDL_Renderer* thisRenderer;
};
} // namespace App::UI

#endif
