#include "player.h"
#include <iostream>

using namespace Constants;

const int Player::LEFT_BOUND = (2 * UNIT_SIZE) + 16;
const int Player::RIGHT_BOUND = SCREEN_WIDTH - (4 * UNIT_SIZE) + 48;
const int Player::UPPER_BOUND = 0;
const int Player::LOWER_BOUND = SCREEN_HEIGHT - UNIT_SIZE;
const int Player::SPEED = 300;

Player::Player(SpriteSheet* spriteSheet, Input* input, Clock* clock)
    : input(input), spriteSheet(spriteSheet), clock(clock) {
    x = SCREEN_WIDTH / 2;
    y = SCREEN_HEIGHT / 2;
    state = AgentState::ALIVE;
    type = AgentType::PLAYER;
    hitbox = {18, 0, 28, UNIT_SIZE};
}

Player::~Player() {
    // No need to destroy the spriteSheet, input, and clock since they are not owned by Player
}

void Player::update() {
    double elapsedTime = clock->getElapsedTime();
    int movementSpeed = static_cast<int>(elapsedTime * SPEED);  // Example speed calculation

    if (input->isKeyHeld(SDL_SCANCODE_UP)) {
        y = std::max(UPPER_BOUND, y - movementSpeed);
    }
    if (input->isKeyHeld(SDL_SCANCODE_DOWN)) {
        y = std::min(LOWER_BOUND, y + movementSpeed);
    }
    if (input->isKeyHeld(SDL_SCANCODE_LEFT)) {
        x = std::max(LEFT_BOUND, x - movementSpeed);
    }
    if (input->isKeyHeld(SDL_SCANCODE_RIGHT)) {
        x = std::min(RIGHT_BOUND, x + movementSpeed);
    }
}

void Player::draw(Graphics& graphics) {
    Agent::draw(graphics, spriteSheet, TextureType::CAR);
}
