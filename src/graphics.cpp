#include "graphics.h"
#include <iostream>

Graphics::Graphics() : window(nullptr), renderer(nullptr), offCanvasTexture(nullptr),
    screenWidth(640), screenHeight(480), offCanvasWidth(640 + 64), offCanvasHeight(480 + 64) {}

Graphics::~Graphics() {
    if (offCanvasTexture) {
        SDL_DestroyTexture(offCanvasTexture);
    }
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}

bool Graphics::initialize() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("My Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    offCanvasTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, offCanvasWidth, offCanvasHeight);
    if (offCanvasTexture == nullptr) {
        std::cerr << "Off-canvas texture could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void Graphics::resetRendition() {
    SDL_SetRenderTarget(renderer, offCanvasTexture);
}

void Graphics::scrollSlice(int offsetX, int offsetY) {
    SDL_SetRenderTarget(renderer, nullptr);

    SDL_Rect srcRect = { offsetX, offsetY, screenWidth, screenHeight };
    SDL_Rect dstRect = { 0, 0, screenWidth, screenHeight };

    SDL_RenderCopy(renderer, offCanvasTexture, &srcRect, &dstRect);
}

void Graphics::present() {
    SDL_RenderPresent(renderer);
}

void Graphics::drawTexture(int x, int y, int size, TextureSlice slice) {
    SDL_Rect dstRect = { x, y, size, size };
    SDL_RenderCopy(renderer, slice.texture, &slice.rect, &dstRect);
}

void Graphics::drawSquare(int x, int y, int size, SDL_Color outlineColor, SDL_Color fillColor) {
    SDL_Rect fillRect = { x, y, size, size };
    SDL_SetRenderDrawColor(renderer, fillColor.r, fillColor.g, fillColor.b, fillColor.a);
    SDL_RenderFillRect(renderer, &fillRect);

    SDL_SetRenderDrawColor(renderer, outlineColor.r, outlineColor.g, outlineColor.b, outlineColor.a);
    SDL_RenderDrawRect(renderer, &fillRect);
}

void Graphics::drawRect(int x, int y, int width, int height, SDL_Color outlineColor, SDL_Color fillColor) {
    SDL_Rect fillRect = { x, y, width, height };
    SDL_SetRenderDrawColor(renderer, fillColor.r, fillColor.g, fillColor.b, fillColor.a);
    SDL_RenderFillRect(renderer, &fillRect);

    SDL_SetRenderDrawColor(renderer, outlineColor.r, outlineColor.g, outlineColor.b, outlineColor.a);
    SDL_RenderDrawRect(renderer, &fillRect); 
}

SDL_Renderer* Graphics::getRenderer() const {
    return renderer;
}
