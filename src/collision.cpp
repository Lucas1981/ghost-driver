#include "collision.h"
#include <SDL_rect.h>  // for SDL_HasIntersection, SDL_Rect
#include "agent.h"     // for Agent

bool checkCollision(const Agent* a, const Agent* b) {
    SDL_Rect rectA = a->getTranslatedHitbox();
    SDL_Rect rectB = b->getTranslatedHitbox();
    return SDL_HasIntersection(&rectA, &rectB);
}
