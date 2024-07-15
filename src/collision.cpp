#include "collision.h"
#include <iostream>

bool checkCollision(const Agent* a, const Agent* b) {
    SDL_Rect rectA = a->get_translated_hitbox();
    SDL_Rect rectB = b->get_translated_hitbox();
    return SDL_HasIntersection(&rectA, &rectB);
}
