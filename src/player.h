#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include "graphics.h"
#include "input.h"
#include "agent.h"
#include "spritesheet.h"
#include "clock.h"
#include "constants.h"

class Player : public Agent {
public:
    Player(SpriteSheet* spriteSheet, Input* input, Clock* clock);
    ~Player();
    void update() override;
    void draw(Graphics& graphics) override;

private:
    static const int LEFT_BOUND;
    static const int RIGHT_BOUND;
    static const int UPPER_BOUND;
    static const int LOWER_BOUND;
    static const int SPEED;

    Input* input;  // Store the input object as a private member
    SpriteSheet* spriteSheet;  // Store the spritesheet object as a private member
    Clock* clock;  // Store the clock object as a private member
};

#endif // PLAYER_H
