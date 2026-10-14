#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "App/UI/SdlFactory.hpp"
#include "App/UI/SdlImage.hpp"
#include "App/UI/SdlPlayerCar.hpp"
#include "App/UI/SdlText.hpp"

using namespace App::UI;

SdlFactory::SdlFactory() : Factory() {
}

SdlFactory::~SdlFactory() {
    close();
}

bool SdlFactory::init() {
    if (!SDL_Init(SDL_INIT_VIDEO)) return true;
    std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
    return false;
}

SDL_Window*   gWindow;
SDL_Renderer* gRenderer;
SDL_Event     event;

/*
 * Show window
 *
 * @ std::string title	: title of the window
 * @ int screen_width	: width of the window
 * @ int screen_height	: height of the window
 */
bool SdlFactory::show(std::string title, int screen_width, int screen_height) {
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        std::cout << "Warning! Linear texture filtering not enabled!" << std::endl;
        return false;
    }
    gWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN);
    if (!gWindow) {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    } else {
        gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
        if (!gRenderer) {
            std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
            return false;
        } else {
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) & imgFlags)) {
                std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
                return false;
            }
            if (TTF_Init() == -1) {
                std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
                return false;
            }
            SDL_RenderClear(gRenderer);
            update();
        }
    }
    return true;
}

void SdlFactory::clear() {
    SDL_RenderClear(gRenderer);
}

void SdlFactory::update() {
    SDL_RenderPresent(gRenderer);
}

void SdlFactory::close() {
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

/*
 * Event handler, returns actions as integers
 */
SdlFactory::Key_t SdlFactory::eventHandler() {
    if (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return SdlFactory::Key_t::KEY_QUIT;
        } else if (event.type == SDL_KEYDOWN && !event.key.repeat) {
            switch (event.key.keysym.sym) {
            case SDLK_UP:
                return SdlFactory::Key_t::KEY_UP_PRESSED;
            case SDLK_DOWN:
                return SdlFactory::Key_t::KEY_DOWN_PRESSED;
            case SDLK_LEFT:
                return SdlFactory::Key_t::KEY_LEFT_PRESSED;
            case SDLK_RIGHT:
                return SdlFactory::Key_t::KEY_RIGHT_PRESSED;
            case SDLK_SPACE:
                return SdlFactory::Key_t::KEY_SPACE;
            case SDLK_p:
                return SdlFactory::Key_t::KEY_P;
            case SDLK_r:
                return SdlFactory::Key_t::KEY_R;
            case SDLK_q:
                return SdlFactory::Key_t::KEY_Q;
            default:
                return SdlFactory::Key_t::KEY_none;
            }
        } else if (event.type == SDL_KEYUP && !event.key.repeat) {
            switch (event.key.keysym.sym) {
            case SDLK_UP:
                return SdlFactory::Key_t::KEY_UP_RELEASED;
            case SDLK_DOWN:
                return SdlFactory::Key_t::KEY_DOWN_RELEASED;
            case SDLK_LEFT:
                return SdlFactory::Key_t::KEY_LEFT_RELEASED;
            case SDLK_RIGHT:
                return SdlFactory::Key_t::KEY_RIGHT_RELEASED;
            default:
                return SdlFactory::Key_t::KEY_none;
            }
        } else {
            return SdlFactory::Key_t::KEY_none;
        }
    }
    return SdlFactory::Key_t::KEY_none;
}

/*
 * Creates and returns new image
 *
 * @ std::string path	: location of the image file
 */
Image* SdlFactory::getNewImage(std::string path) {
    Image* newImage = new SdlImage(path, gRenderer);
    return newImage;
}

/*
 * Creates and returns new text
 *
 * @ std::string path			: location of the ttf file
 * @ int size					: size of the text
 * @ std::string text			: text to save in texture
 * @ int red					: value red (0 - 255)
 * @ int green					: value green (0 - 255)
 * @ int blue					: value blue (0 - 255)
 */
Text* SdlFactory::getNewText(std::string path, int size, std::string text, int red, int green, int blue) {
    Text* newText = new SDL_Text(path, size, gRenderer, text, red, green, blue);
    return newText;
}

/*
 * Creates and returns new player car
 *
 * @ std::string path	: location of the image file
 */
PlayerCar* SdlFactory::getNewPlayerCar(std::string path) {
    PlayerCar* newPlayerCar = new SdlPlayerCar(path, gRenderer);
    return newPlayerCar;
}
