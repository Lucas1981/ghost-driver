#include "agent.h"

SDL_Rect Agent::getTranslatedHitbox() const {
    return SDL_Rect { x + hitbox.x, y + hitbox.y, hitbox.w, hitbox.h };
}
