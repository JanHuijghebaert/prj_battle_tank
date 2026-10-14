#ifndef __APP_UI_SDLTEXTURE__HPP__
#define __APP_UI_SDLTEXTURE__HPP__

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

namespace App::UI {
class SdlTexture {
  public:
    SdlTexture();
    ~SdlTexture();
    bool loadFromFile(std::string path, SDL_Renderer* gRenderer);
    bool loadFromRenderedText(std::string path, int size, SDL_Renderer* gRenderer, std::string text, SDL_Color color);
    void free();
    void setColor(Uint8 red, Uint8 green, Uint8 blue);
    void render(SDL_Renderer* gRenderer, int x, int y);

    int mWidth;
    int mHeight;

  private:
    SDL_Texture* mTexture;
};
} // namespace App::UI

#endif
