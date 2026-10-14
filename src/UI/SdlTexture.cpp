#include "App/UI/SdlTexture.hpp"

using namespace App::UI;

SdlTexture::SdlTexture() {
    mTexture = NULL;
    mWidth   = 0;
    mHeight  = 0;
}

SdlTexture::~SdlTexture() {
    free();
}

/*
 * Load file in texture
 *
 * @ std::string path			: location of the image file
 * @ SDL_Renderer* gRenderer	: SDL renderer from SDL factory
 */
bool SdlTexture::loadFromFile(std::string path, SDL_Renderer* gRenderer) {
    free();
    SDL_Texture* newTexture    = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (!loadedSurface) {
        std::cout << "Unable to load image " << path.c_str() << "! SDL_image_Error: " << IMG_GetError() << std::endl;
        return false;
    } else {
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0xFF, 0xFF));
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (!newTexture) {
            std::cout << "Unable to create texture from " << path.c_str() << "! SDL_Error: " << SDL_GetError() << std::endl;
            return false;
        } else {
            mWidth  = loadedSurface->w;
            mHeight = loadedSurface->h;
        }
        SDL_FreeSurface(loadedSurface);
    }
    mTexture = newTexture;
    return (bool)mTexture;
}

/*
 * Load text in texture
 *
 * @ std::string path			: location of the ttf file
 * @ int size					: size of the text
 * @ SDL_Renderer* gRenderer	: SDL renderer from SDL factory
 * @ std::string text			: text to save in texture
 * @ SDL_Color color			: color of the text
 */
bool SdlTexture::loadFromRenderedText(std::string path, int size, SDL_Renderer* gRenderer, std::string text, SDL_Color color) {
    free();
    TTF_Font* gFont = NULL;
    gFont           = TTF_OpenFont(path.c_str(), size);
    if (!gFont) {
        std::cout << "Failed to load font! SDL_ttf_Error: " << TTF_GetError() << std::endl;
        return false;
    }
    SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, text.c_str(), color);
    if (!textSurface) {
        std::cout << "Unable to create text surface! SDL_ttf_Error: " << TTF_GetError() << std::endl;
        return false;
    } else {
        mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
        if (!mTexture) {
            std::cout << "Unable to create texture from text! SDL_Error: " << SDL_GetError() << std::endl;
            return false;
        } else {
            mWidth  = textSurface->w;
            mHeight = textSurface->h;
        }
        SDL_FreeSurface(textSurface);
        textSurface = NULL;
        TTF_CloseFont(gFont);
        gFont = NULL;
    }
    return true;
}

/*
 * Destroy texture
 */
void SdlTexture::free() {
    if (!mTexture) return;
    SDL_DestroyTexture(mTexture);
    mTexture = NULL;
    mWidth   = 0;
    mHeight  = 0;
}

/*
 * Multiply color
 *
 * @ Uint8 red	: red value (0 - 255)
 * @ Uint8 green: green value (0 - 255)
 * @ Uint8 blue	: blue value (0 - 255)
 */
void SdlTexture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
    SDL_SetTextureColorMod(mTexture, red, green, blue);
}

/*
 * Render texture
 *
 * @ SDL_Renderer* gRenderer	: SDL renderer from SDL factory
 * @ int x						: x location on screen
 * @ int y						: y location on screen
 */
void SdlTexture::render(SDL_Renderer* gRenderer, int x, int y) {
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};
    SDL_RenderCopy(gRenderer, mTexture, NULL, &renderQuad);
}
