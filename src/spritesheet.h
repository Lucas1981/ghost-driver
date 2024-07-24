#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <SDL_rect.h>     // for SDL_Rect
#include <SDL_render.h>   // for SDL_Texture, SDL_Renderer
#include <string>         // for string
#include <unordered_map>  // for unordered_map

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
    std::unordered_map<TextureType, SDL_Rect> textureMap;
};

#endif // SPRITESHEET_H
