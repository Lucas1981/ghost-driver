#include "opponent.h"
#include <iostream>
#include <random> // Include the random header

// Define and initialize static members
std::mt19937 Opponent::gen(std::random_device{}());
std::uniform_int_distribution<> Opponent::dis((2 * 64) + 16, 640 - (4 * 64) + 48);

Opponent::Opponent(SDL_Renderer* renderer, SpriteSheet* spriteSheet, Clock* clock)
    : renderer(renderer), spriteSheet(spriteSheet), clock(clock) {
    x = getRandomX();
    y = -64;
    state = State::ALIVE;
    type = Type::OPPONENT;
    hitbox = {18, 0, 64 - 36, 64};
}

Opponent::~Opponent() {
    // No need to destroy the spriteSheet since it is not owned by Opponent
}

int Opponent::getRandomX() {
    return dis(gen);
}

void Opponent::update() {
    double elapsedTime = clock->getElapsedTime();
    int movementSpeed = static_cast<int>(elapsedTime * 320);  // Example speed calculation

    // Implement opponent-specific update logic here
    y += movementSpeed; // Move downwards for demonstration

    if (y > 480 + 64) {
        state = State::DEAD;     
    }
}

void Opponent::draw(Graphics& graphics) {
    TextureSlice slice = spriteSheet->getTextureSlice(TextureType::OPPONENT);  // Assuming TextureType::CAR is defined
    graphics.drawTexture(x, y, 64, slice);  // Draw the opponent using the spritesheet
}
