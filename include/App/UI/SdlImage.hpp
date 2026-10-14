#ifndef __APP_UI_SDLIMAGE__HPP__
#define __APP_UI_SDLIMAGE__HPP__

#include <iostream>
#include <SDL2/SDL.h>
#include "App/Core/Image.hpp"
#include "App/UI/SdlTexture.hpp"

using namespace App::Core;

namespace App::UI {
class SdlImage : public Image {
  public:
    /**
     * @brief Constructor
     * @param path Location to image file
     * @param gRenderer SDL renderer
     */
    SdlImage(std::string path, SDL_Renderer* gRenderer);

    int getWidth();
    int getHeight();

    /**
     * @brief Multiplies color
     * @param red Color red value (0 - 255)
     * @param green Color green value (0 - 255)
     * @param blue Color blue value (0 - 255)
     */
    void modulateColor(int red, int green, int blue);
    void visualize();

  private:
    SdlTexture    thisTexture;
    SDL_Renderer* thisRenderer;
};
} // namespace App::UI

#endif
