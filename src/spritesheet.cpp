#include "spritesheet.h"
#include <iostream>

SpriteSheet::SpriteSheet(SDL_Renderer* renderer, const std::string& filePath) : renderer(renderer), texture(nullptr) {
    texture = IMG_LoadTexture(renderer, filePath.c_str());
    if (!texture) {
        std::cerr << "Failed to load texture: " << IMG_GetError() << std::endl;
    } else {
        initializeTextures();
    }
}

SpriteSheet::~SpriteSheet() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

void SpriteSheet::initializeTextures() {
    // Define texture slices for each texture type
    textureMap[TextureType::STRIPED_ROAD] = { 0, 0, 64, 64 };
    textureMap[TextureType::PLAIN_ROAD] = { 192, 0, 64, 64 };
    textureMap[TextureType::GRASS] = { 64, 0, 64, 64 };
    textureMap[TextureType::CAR] = { 128, 0, 64, 64 };
    textureMap[TextureType::OPPONENT] = { 0, 64, 64, 64 };
    textureMap[TextureType::EXPLOSION] = { 64, 64, 64, 64 };
    // Add other texture mappings here
}

TextureSlice SpriteSheet::getTextureSlice(TextureType type) {
    return { texture, textureMap[type] };
}
