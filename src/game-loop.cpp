#include "game-loop.h"
#include "collision.h"
#include <cmath> // Include the cmath header for std::fmod
#include <iostream>

const int GameLoop::ROAD_SPEED = 256;

GameLoop::GameLoop() : gameState(GameState::TITLE_SCREEN), offsetX(32.0), offsetY(0.0), createOpponentTimer(0.0) {}

GameLoop::~GameLoop() {
    cleanup();
}

void GameLoop::run() {
    if (!initialize()) {
        std::cerr << "Failed to initialize!" << std::endl;
        return;
    }

    while (!input.shouldQuit()) {
        clock.setTimer();
        input.update();
        update();
        render();
    }
}

bool GameLoop::initialize() {
    if (!graphics.initialize()) {
        std::cerr << "Failed to initialize graphics!" << std::endl;
        return false;
    }
    spriteSheet = new SpriteSheet(graphics.getRenderer(), "../assets/tiles.png");
    agents.push_back(new Player(graphics.getRenderer(), spriteSheet, &input, &clock));
    grid = new Grid("../assets/grid.txt", graphics, *spriteSheet);  // Initialize Grid with file path
    if (!grid->loadGrid()) {
        std::cerr << "Failed to load grid!" << std::endl;
        return false;
    }
    return true;
}

void GameLoop::update() {
    using namespace Constants;

    double elapsedTime = clock.getElapsedTime();

    createOpponentTimer += elapsedTime;

    // Add a new opponent every 300 ms
    if (createOpponentTimer >= 0.3) {
        agents.push_back(new Opponent(graphics.getRenderer(), spriteSheet, &clock));
        createOpponentTimer = 0.0; // Reset the timer
    }

    for (auto it = agents.begin(); it != agents.end(); ) {
        Agent* agent = *it;
        agent->update();
        
        // Check if the agent should be removed
        if (!agent->isAlive() && !agent->isPlayer()) {
            it = agents.erase(it); // Remove from list and get the next iterator
            delete agent; // Free the memory
        } else {
            ++it; // Move to the next element
        }
    }

   // Find the player agent
    Agent* player = nullptr;
    for (auto agent : agents) {
        if (agent->isPlayer()) {
            player = agent;
            break;
        }
    }

    // Check for collisions between player and opponents
    if (player != nullptr) {
        for (auto agent : agents) {
            if (!agent->isPlayer() && checkCollision(player, agent)) {
                std::cout << "Collision!" << std::endl;
            } else {
                std::cout << std::endl;
            }
        }
    }

    // Update game state
    offsetY = std::fmod(offsetY + UNIT_SIZE - (ROAD_SPEED * elapsedTime), UNIT_SIZE);
}

void GameLoop::render() {
    // Clear off-screen canvas
    graphics.resetRendition();

    // Draw the grid on the off-screen canvas
    grid->drawGrid();

    // Copy a slice of the off-screen canvas back to itself to simulate scrolling
    graphics.scrollSlice((int)offsetX, (int)offsetY);

    // Draw all agents on the off-screen canvas
    for (auto agent : agents) {
        agent->draw(graphics); // No offset needed
    }

    graphics.present();
}

void GameLoop::cleanup() {
    delete spriteSheet;
    delete grid;
    for (auto agent : agents) {
        delete agent;
    }
}
