#include "App/UI/SdlImage.hpp"

using namespace App::UI;

SdlImage::SdlImage(std::string path, SDL_Renderer* gRenderer) : Image() {
    thisTexture.loadFromFile(path, gRenderer);
    thisRenderer = gRenderer;
}

int SdlImage::getWidth() {
    return thisTexture.mWidth;
}

int SdlImage::getHeight() {
    return thisTexture.mHeight;
}

void SdlImage::modulateColor(int red, int green, int blue) {
    thisTexture.setColor(red, green, blue);
}

void SdlImage::visualize() {
    thisTexture.render(thisRenderer, this->x, this->y);
}
