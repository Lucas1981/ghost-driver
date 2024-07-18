#ifndef UI_H
#define UI_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class UI {
public:
    UI();
    ~UI();

    bool initialize(SDL_Renderer* renderer, const std::string& fontPath, int fontSize);
    void renderText(SDL_Renderer* renderer, const std::string& text, int x, int y);
    void renderInterpolatedText(SDL_Renderer* renderer, const std::string& text, double value, int x, int y);

private:
    static constexpr SDL_Color greyOutline = { 128, 128, 128, 255 }; // RGB values for grey and 255 for full opacity
    static constexpr SDL_Color whiteFill = { 255, 255, 255, 255 };  // RGB values for white and 255 for full opacity
    TTF_Font* font;
};

#endif // UI_H
