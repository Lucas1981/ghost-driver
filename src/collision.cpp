#include "collision.h"
#include <iostream>

bool checkCollision(const Agent* a, const Agent* b) {
    SDL_Rect rectA = a->getTranslatedHitbox();
    SDL_Rect rectB = b->getTranslatedHitbox();
    return SDL_HasIntersection(&rectA, &rectB);
}
