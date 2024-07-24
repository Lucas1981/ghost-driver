#include "title-screen.h"
#include <SDL_error.h>       // for SDL_GetError
#include <SDL_rect.h>        // for SDL_Rect
#include <SDL_surface.h>     // for SDL_FreeSurface, SDL_Surface
#include <iostream>          // for basic_ostream, operator<<, endl, cerr
#include "SDL2/SDL_image.h"  // for IMG_Load, IMG_GetError

TitleScreen::TitleScreen() : titleTexture(nullptr), width(0), height(0) {}

TitleScreen::~TitleScreen() {
    if (titleTexture) {
        SDL_DestroyTexture(titleTexture);
    }
}

bool TitleScreen::loadTitleScreen(SDL_Renderer* renderer, const std::string& filePath) {
    SDL_Surface* tempSurface = IMG_Load(filePath.c_str());
    if (!tempSurface) {
        std::cerr << "Failed to load image: " << filePath << " SDL_image Error: " << IMG_GetError() << std::endl;
        return false;
    }

    titleTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    if (!titleTexture) {
        std::cerr << "Failed to create texture from surface: " << filePath << " SDL Error: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(tempSurface);
        return false;
    }

    width = tempSurface->w;
    height = tempSurface->h;

    SDL_FreeSurface(tempSurface);
    return true;
}

void TitleScreen::drawTitleScreen(SDL_Renderer* renderer) {
    if (titleTexture) {
        SDL_Rect dstRect = {0, 0, width, height};
        SDL_RenderCopy(renderer, titleTexture, nullptr, &dstRect);
    }
}
