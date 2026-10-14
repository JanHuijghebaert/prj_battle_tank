#ifndef __APP_UI_SDLTEXT__HPP__
#define __APP_UI_SDLTEXT__HPP__

#include <SDL2/SDL.h>
#include <iostream>

#include "App/Core/Text.hpp"
#include "App/UI/SdlTexture.hpp"

using namespace App::Core;

namespace App::UI {
class SDL_Text : public Text {
  public:
    /**
     * @brief Constructor
     * @param path      Location of the TTF file
     * @param size      Size of the text
     * @param gRenderer SDL renderer
     * @param text      Text to save in texture
     * @param red       Red value (0 - 255)
     * @param green     Green value (0 - 255)
     * @param blue      Blue value (0 - 255)
     */
    SDL_Text(std::string path, int size, SDL_Renderer* gRenderer, std::string text, int red, int green, int blue);
    ~SDL_Text();

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
     * @brief Set text
     * @param text Texture text
     * @param red  Color red value (0 - 255)
     * @param green Color green value (0 - 255)
     * @param blue Color blue value (0 - 255)
     */
    void setText(std::string text, int red, int green, int blue);

    /**
     * @brief Visualize text
     */
    void visualize();

    std::string path;
    int         size;

  private:
    SdlTexture    thisTexture;
    SDL_Renderer* thisRenderer;
};
} // namespace App::UI

#endif
