#include "opponent.h"
#include <iostream>
#include <random> // Include the random header

using namespace Constants;

const int Opponent::THRESHOLD = SCREEN_WIDTH + UNIT_SIZE;
const int Opponent::SPEED = 320;

// Define and initialize static members
std::mt19937 Opponent::gen(std::random_device{}());
std::uniform_int_distribution<> Opponent::dis((2 * UNIT_SIZE) + 16, SCREEN_WIDTH - (4 * UNIT_SIZE) + 48);

Opponent::Opponent(SDL_Renderer* renderer, SpriteSheet* spriteSheet, Clock* clock)
    : renderer(renderer), spriteSheet(spriteSheet), clock(clock) {
    x = getRandomX();
    y = -64;
    state = AgentState::ALIVE;
    type = AgentType::OPPONENT;
    hitbox = {18, 0, 28, UNIT_SIZE};
}

Opponent::~Opponent() {
    // No need to destroy the spriteSheet since it is not owned by Opponent
}

int Opponent::getRandomX() {
    return dis(gen);
}

void Opponent::update() {
    double elapsedTime = clock->getElapsedTime();
    int movementSpeed = static_cast<int>(elapsedTime * SPEED);  // Example speed calculation

    // Implement opponent-specific update logic here
    y += movementSpeed; // Move downwards for demonstration

    if (y > THRESHOLD) {
        state = AgentState::DEAD;     
    }
}

void Opponent::draw(Graphics& graphics) {
    Agent::draw(graphics, spriteSheet, TextureType::OPPONENT);
}
