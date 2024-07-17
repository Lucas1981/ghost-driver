#ifndef OPPONENT_H
#define OPPONENT_H

#include <SDL2/SDL.h>
#include "agent.h"
#include "graphics.h"
#include "spritesheet.h"
#include "clock.h"
#include "constants.h"
#include <random>

class Opponent : public Agent {
public:
    Opponent(SDL_Renderer* renderer, SpriteSheet* spriteSheet, Clock* clock);
    ~Opponent();
    void update() override;
    void draw(Graphics& graphics) override;

private:
    SDL_Renderer* renderer;
    SpriteSheet* spriteSheet;
    Clock* clock;  // Store the clock object as a private member

    static const int THRESHOLD;
    static const int SPEED;
    static std::mt19937 gen; // Random number generator
    static std::uniform_int_distribution<> dis; // Distribution for x coordinate

    static int getRandomX();
};

#endif // OPPONENT_H
