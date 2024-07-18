#ifndef TITLE_SCREEN_H
#define TITLE_SCREEN_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class TitleScreen {
public:
    TitleScreen();
    ~TitleScreen();

    bool loadTitleScreen(SDL_Renderer* renderer, const std::string& filePath);
    void drawTitleScreen(SDL_Renderer* renderer);

private:
    SDL_Texture* titleTexture;
    int width;
    int height;
};

#endif // TITLE_SCREEN_H
