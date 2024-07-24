#include "agent.h"
#include "constants.h"    // for UNIT_SIZE
#include "graphics.h"     // for Graphics
#include "spritesheet.h"  // for TextureSlice, SpriteSheet, TextureType

SDL_Rect Agent::getTranslatedHitbox() const {
    return SDL_Rect { x + hitbox.x, y + hitbox.y, hitbox.w, hitbox.h };
}

void Agent::draw(Graphics& graphics, SpriteSheet* spriteSheet, TextureType localType) {
    using namespace Constants;
    TextureSlice slice = spriteSheet->getTextureSlice(localType);
    graphics.drawTexture(x, y, UNIT_SIZE, slice);

    if (state == AgentState::CRASHED) {
        TextureSlice explosionSlice = spriteSheet->getTextureSlice(TextureType::EXPLOSION);
        graphics.drawTexture(x, y, UNIT_SIZE, explosionSlice);
    }
}