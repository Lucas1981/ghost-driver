#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include <SDL2/SDL_ttf.h>     // for TTF_Font
#include <string>             // for string
#include "SDL2/SDL_pixels.h"  // for SDL_Color
#include "SDL2/SDL_render.h"  // for SDL_Renderer

class UI {
public:
    enum class TextAlign {
        LEFT,
        CENTER,
        RIGHT
    };

    UI();
    ~UI();

    bool initialize(const std::string& fontPath, int fontSize);
    void renderText(SDL_Renderer* renderer, const std::string& text, int x, int y, TextAlign align = TextAlign::LEFT);
    void renderInterpolatedText(SDL_Renderer* renderer, const std::string& text, double value, int x, int y, TextAlign align = TextAlign::LEFT);
    void cleanup();

private:
    TTF_Font* font;
    SDL_Color whiteFill = { 255, 255, 255, 255 };
    SDL_Color greyOutline = { 128, 128, 128, 255 };

    void renderOutlinedText(SDL_Renderer* renderer, const std::string& text, int x, int y, SDL_Color textColor, SDL_Color outlineColor, TextAlign align);
};

#endif // USER_INTERFACE_H
