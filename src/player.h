#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include "graphics.h"
#include "input.h"
#include "agent.h"
#include "spritesheet.h"
#include "clock.h"

class Player : public Agent {
public:
    Player(SDL_Renderer* renderer, SpriteSheet* spriteSheet, Input* input, Clock* clock);
    ~Player();
    void update() override;
    void draw(Graphics& graphics, int offset_x, int offset_y) override;

private:
    SDL_Renderer* renderer;
    Input* input;  // Store the input object as a private member
    SpriteSheet* spriteSheet;  // Store the spritesheet object as a private member
    Clock* clock;  // Store the clock object as a private member
};

#endif // PLAYER_H
