#include "agent.h"

SDL_Rect Agent::getTranslatedHitbox() const {
    return SDL_Rect { x + hitbox.x, y + hitbox.y, hitbox.w, hitbox.h };
}

void Agent::draw(Graphics& graphics, SpriteSheet* spriteSheet, TextureType type) {
    using namespace Constants;
    TextureSlice slice = spriteSheet->getTextureSlice(type);
    graphics.drawTexture(x, y, UNIT_SIZE, slice);

    if (state == AgentState::CRASHED) {
        TextureSlice explosionSlice = spriteSheet->getTextureSlice(TextureType::EXPLOSION);
        graphics.drawTexture(x, y, UNIT_SIZE, explosionSlice);
    }
}