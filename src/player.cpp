#include "player.h"
#include <iostream>

Player::Player(SDL_Renderer* renderer, SpriteSheet* spriteSheet, Input* input, Clock* clock)
    : renderer(renderer), input(input), spriteSheet(spriteSheet), clock(clock) {
    x = 320;
    y = 240;
    state = State::ALIVE;
    type = Type::PLAYER;
    hitbox = {18, 0, 64 - 36, 64};
}

Player::~Player() {
    // No need to destroy the spriteSheet, input, and clock since they are not owned by Player
}

void Player::update() {
    double elapsedTime = clock->getElapsedTime();
    int movementSpeed = static_cast<int>(elapsedTime * 300);  // Example speed calculation

    if (input->isKeyHeld(SDL_SCANCODE_UP)) {
        y = std::max(0, y - movementSpeed);
    }
    if (input->isKeyHeld(SDL_SCANCODE_DOWN)) {
        y = std::min(480 - 64, y + movementSpeed);
    }
    if (input->isKeyHeld(SDL_SCANCODE_LEFT)) {
        x = std::max((2 * 64) + 16, x - movementSpeed);
    }
    if (input->isKeyHeld(SDL_SCANCODE_RIGHT)) {
        x = std::min(640 - (4 * 64) + 48, x + movementSpeed);
    }
}

void Player::draw(Graphics& graphics) {
    TextureSlice slice = spriteSheet->getTextureSlice(TextureType::CAR);  // Assuming TextureType::CAR is defined
    graphics.drawTexture(x, y, 64, slice);  // Draw the player using the spritesheet
}
