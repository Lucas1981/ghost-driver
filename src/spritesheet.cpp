#include "spritesheet.h"
#include <iostream>

using namespace Constants;

SpriteSheet::SpriteSheet(SDL_Renderer* renderer, const std::string& filePath) {
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
    textureMap[TextureType::STRIPED_ROAD] = { 0, 0, UNIT_SIZE, UNIT_SIZE };
    textureMap[TextureType::PLAIN_ROAD] = { 3 * UNIT_SIZE, 0, UNIT_SIZE, UNIT_SIZE };
    textureMap[TextureType::GRASS] = { UNIT_SIZE, 0, UNIT_SIZE, UNIT_SIZE };
    textureMap[TextureType::CAR] = { 2 * UNIT_SIZE, 0, UNIT_SIZE, UNIT_SIZE };
    textureMap[TextureType::OPPONENT] = { 0, UNIT_SIZE, UNIT_SIZE, UNIT_SIZE };
    textureMap[TextureType::EXPLOSION] = { UNIT_SIZE, UNIT_SIZE, UNIT_SIZE, UNIT_SIZE };
    // Add other texture mappings here
}

TextureSlice SpriteSheet::getTextureSlice(TextureType type) {
    return { texture, textureMap[type] };
}
