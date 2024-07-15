#ifndef OPPONENT_H
#define OPPONENT_H

#include <SDL2/SDL.h>
#include "agent.h"
#include "graphics.h"
#include "spritesheet.h"
#include "clock.h"

class Opponent : public Agent {
public:
    Opponent(SDL_Renderer* renderer, SpriteSheet* spriteSheet, Clock* clock);
    ~Opponent();
    void update() override;
    void draw(Graphics& graphics, int offset_x, int offset_y) override;

private:
    SDL_Renderer* renderer;
    SpriteSheet* spriteSheet;
    Clock* clock;  // Store the clock object as a private member

    int get_random_x();
};

#endif // OPPONENT_H
