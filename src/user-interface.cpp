#include "user-interface.h"
#include <iostream>

UI::UI() : font(nullptr) {}

UI::~UI() {
    cleanup();
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

void UI::renderOutlinedText(SDL_Renderer* renderer, const std::string& text, int x, int y, SDL_Color textColor, SDL_Color outlineColor, TextAlign align) {
    // Create surface and texture for the outline text
    SDL_Surface* outlineSurface = TTF_RenderText_Solid(font, text.c_str(), outlineColor);
    if (!outlineSurface) {
        std::cerr << "Failed to create outline text surface: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Texture* outlineTexture = SDL_CreateTextureFromSurface(renderer, outlineSurface);
    if (!outlineTexture) {
        std::cerr << "Failed to create outline text texture: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(outlineSurface);
        return;
    }

    // Create surface and texture for the main text
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    if (!textSurface) {
        std::cerr << "Failed to create text surface: " << TTF_GetError() << std::endl;
        SDL_FreeSurface(outlineSurface);
        SDL_DestroyTexture(outlineTexture);
        return;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!textTexture) {
        std::cerr << "Failed to create text texture: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(outlineSurface);
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(outlineTexture);
        return;
    }

    // Get the width and height of the text
    int textWidth = textSurface->w;
    int textHeight = textSurface->h;

    // Adjust x and y based on alignment
    int adjustedX = x;
    int adjustedY = y;
    switch (align) {
        case TextAlign::CENTER:
            adjustedX -= textWidth / 2;
            adjustedY -= textHeight / 2;
            break;
        case TextAlign::RIGHT:
            adjustedX -= textWidth;
            break;
        case TextAlign::LEFT:
        default:
            break;
    }

    // Render the outline text at slightly offset positions
    SDL_Rect outlineRect = { adjustedX - 1, adjustedY - 1, textWidth, textHeight };
    SDL_RenderCopy(renderer, outlineTexture, nullptr, &outlineRect);
    outlineRect = { adjustedX + 1, adjustedY - 1, textWidth, textHeight };
    SDL_RenderCopy(renderer, outlineTexture, nullptr, &outlineRect);
    outlineRect = { adjustedX - 1, adjustedY + 1, textWidth, textHeight };
    SDL_RenderCopy(renderer, outlineTexture, nullptr, &outlineRect);
    outlineRect = { adjustedX + 1, adjustedY + 1, textWidth, textHeight };
    SDL_RenderCopy(renderer, outlineTexture, nullptr, &outlineRect);

    // Render the main text on top of the outline text
    SDL_Rect textRect = { adjustedX, adjustedY, textWidth, textHeight };
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

    // Clean up surfaces and textures
    SDL_FreeSurface(outlineSurface);
    SDL_DestroyTexture(outlineTexture);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

void UI::renderText(SDL_Renderer* renderer, const std::string& text, int x, int y, TextAlign align) {
    renderOutlinedText(renderer, text, x, y, whiteFill, greyOutline, align);
}

void UI::renderInterpolatedText(SDL_Renderer* renderer, const std::string& text, double value, int x, int y, TextAlign align) {
    std::string interpolatedText = text + std::to_string(static_cast<int>(value));
    renderText(renderer, interpolatedText, x, y, align);
}

void UI::cleanup() {
    if (font) {
        TTF_CloseFont(font);
        font = nullptr;
    }
    TTF_Quit();
}
