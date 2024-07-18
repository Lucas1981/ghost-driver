#include "user-interface.h"
#include <iostream>

UI::UI() : font(nullptr) {}

UI::~UI() {
    if (font) {
        TTF_CloseFont(font);
    }
    TTF_Quit();
}

bool UI::initialize(SDL_Renderer* renderer, const std::string& fontPath, int fontSize) {
    if (TTF_Init() == -1) {
        std::cerr << "Failed to initialize SDL_ttf: " << TTF_GetError() << std::endl;
        return false;
    }

    font = TTF_OpenFont(fontPath.c_str(), fontSize);
    if (!font) {
        std::cerr << "Failed to load font: " << fontPath << " SDL_ttf Error: " << TTF_GetError() << std::endl;
        return false;
    }

    return true;
}

void UI::renderText(SDL_Renderer* renderer, const std::string& text, int x, int y) {
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), whiteFill);
    if (!textSurface) {
        std::cerr << "Failed to create text surface: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!textTexture) {
        std::cerr << "Failed to create text texture: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(textSurface);
        return;
    }

    SDL_Rect renderQuad = { x, y, textSurface->w, textSurface->h };
    SDL_RenderCopy(renderer, textTexture, nullptr, &renderQuad);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

void UI::renderInterpolatedText(SDL_Renderer* renderer, const std::string& text, double value, int x, int y) {
    std::string interpolatedText = text + std::to_string(static_cast<int>(value));
    renderText(renderer, interpolatedText, x, y);
}
