#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL_pixels.h>  // for SDL_Color
#include <SDL_render.h>  // for SDL_Renderer, SDL_Texture
#include <SDL_video.h>   // for SDL_Window
struct TextureSlice;

class Graphics {
public:
    Graphics();
    ~Graphics();
    bool initialize();
    void resetRendition();
    void scrollSlice(int offsetX, int offsetY);
    void present();
    void drawSquare(int x, int y, int size, SDL_Color outlineColor, SDL_Color fillColor);
    void drawRect(int x, int y, int width, int height, SDL_Color outlineColor, SDL_Color fillColor);
    void drawTexture(int x, int y, int size, TextureSlice slice);
    SDL_Renderer* getRenderer() const;  // Getter for the renderer

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* offCanvasTexture;
    int screenWidth;
    int screenHeight;
    int offCanvasWidth;
    int offCanvasHeight;
};

#endif // GRAPHICS_H
