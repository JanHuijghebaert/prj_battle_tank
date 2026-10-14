#include "App/UI/SdlText.hpp"

using namespace App::Core;
using namespace App::UI;

SDL_Text::SDL_Text(std::string path, int size, SDL_Renderer* gRenderer, std::string text, int red, int green, int blue) : Text() {
    SDL_Color color;
    color.r = red;
    color.g = green;
    color.b = blue;
    thisTexture.loadFromRenderedText(path, size, gRenderer, text, color);
    thisRenderer = gRenderer;
    this->path   = path;
    this->size   = size;
}

SDL_Text::~SDL_Text() {
}

int SDL_Text::getWidth() {
    return thisTexture.mWidth;
}

int SDL_Text::getHeight() {
    return thisTexture.mHeight;
}

void SDL_Text::setText(std::string text, int red, int green, int blue) {
    SDL_Color color;
    color.r = red;
    color.g = green;
    color.b = blue;
    thisTexture.loadFromRenderedText(path, size, thisRenderer, text, color);
}

void SDL_Text::visualize() {
    thisTexture.render(thisRenderer, this->x, this->y);
}
