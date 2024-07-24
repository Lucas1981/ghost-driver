#ifndef OPPONENT_H
#define OPPONENT_H

#include <random>   // for mt19937, uniform_int_distribution
#include "agent.h"  // for Agent
class Clock;
class Graphics;
class SpriteSheet;

class Opponent : public Agent {
public:
    Opponent(SpriteSheet* spriteSheet, Clock* clock);
    ~Opponent();
    void update() override;
    void draw(Graphics& graphics) override;

private:
    SpriteSheet* spriteSheet;
    Clock* clock;  // Store the clock object as a private member

    static const int THRESHOLD;
    static constexpr int SPEED = 600;
    static std::mt19937 gen; // Random number generator
    static std::uniform_int_distribution<> dis; // Distribution for x coordinate

    static int getRandomX();
};

#endif // OPPONENT_H
