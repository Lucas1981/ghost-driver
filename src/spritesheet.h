#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <unordered_map>
#include "constants.h"

enum class TextureType {
    STRIPED_ROAD,
    PLAIN_ROAD,
    GRASS,
    CAR,
    OPPONENT,
    EXPLOSION
    // Add other texture types here
};

struct TextureSlice {
    SDL_Texture* texture;
    SDL_Rect rect;
};

class SpriteSheet {
public:
    SpriteSheet(SDL_Renderer* renderer, const std::string& filePath);
    ~SpriteSheet();
    TextureSlice getTextureSlice(TextureType type);

private:
    void initializeTextures();

    SDL_Texture* texture;
    SDL_Renderer* renderer;
    std::unordered_map<TextureType, SDL_Rect> textureMap;
};

#endif // SPRITESHEET_H
