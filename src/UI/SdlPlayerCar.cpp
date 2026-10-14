#include "App/UI/SdlPlayerCar.hpp"

using namespace App::Core;
using namespace App::UI;

SdlPlayerCar::SdlPlayerCar(std::string path, SDL_Renderer* gRenderer) : PlayerCar() {
    thisTexture.loadFromFile(path, gRenderer);
    thisRenderer = gRenderer;
}

SdlPlayerCar::~SdlPlayerCar() {
}

int SdlPlayerCar::getWidth() {
    return thisTexture.mWidth;
}

int SdlPlayerCar::getHeight() {
    return thisTexture.mHeight;
}

void SdlPlayerCar::visualize() {
    thisTexture.render(thisRenderer, this->x, this->y);
}
