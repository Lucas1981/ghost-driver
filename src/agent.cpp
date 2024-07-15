#include "agent.h"

SDL_Rect Agent::get_translated_hitbox() const {
    return SDL_Rect { x + hitbox.x, y + hitbox.y, hitbox.w, hitbox.h };
}
