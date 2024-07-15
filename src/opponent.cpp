#include "opponent.h"
#include <iostream>
#include <random> // Include the random header

Opponent::Opponent(SDL_Renderer* renderer, SpriteSheet* spriteSheet, Clock* clock)
    : renderer(renderer), spriteSheet(spriteSheet), clock(clock) {
    x = get_random_x();
    y = -64;
    state = State::ALIVE;
    type = Type::OPPONENT;
    hitbox = {18, 0, 64 - 36, 64};
}

Opponent::~Opponent() {
    // No need to destroy the spriteSheet since it is not owned by Opponent
}

int Opponent::get_random_x() {
    std::random_device rd; // Random device for seeding
    std::mt19937 gen(rd()); // Mersenne Twister RNG
    std::uniform_int_distribution<> dis((2 * 64) + 16, 640 - (4 * 64) + 48); // Uniform distribution for x coordinate
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

void Opponent::draw(Graphics& graphics, int offset_x, int offset_y) {
    TextureSlice slice = spriteSheet->getTextureSlice(TextureType::OPPONENT);  // Assuming TextureType::CAR is defined
    graphics.drawTexture(x + offset_x, y + offset_y, 64, slice);  // Draw the opponent using the spritesheet
}