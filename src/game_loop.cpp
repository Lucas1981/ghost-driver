#include "game_loop.h"
#include "collision.h"
#include <cmath> // Include the cmath header for std::fmod
#include <iostream>

GameLoop::GameLoop() : gameState(GameState::TITLE_SCREEN), offset_x(32.0), offset_y(0.0), create_opponent_timer(0.0) {}

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

    // Add a single opponent
    agents.push_back(new Opponent(graphics.getRenderer(), spriteSheet, &clock));
    
    grid = new Grid("../assets/grid.txt");  // Initialize Grid with file path
    if (!grid->loadGrid()) {
        std::cerr << "Failed to load grid!" << std::endl;
        return false;
    }
    return true;
}

void GameLoop::update() {
    double elapsedTime = clock.getElapsedTime();

    create_opponent_timer += elapsedTime;

    // Add a new opponent every 300 ms
    if (create_opponent_timer >= 0.3) {
        agents.push_back(new Opponent(graphics.getRenderer(), spriteSheet, &clock));
        create_opponent_timer = 0.0; // Reset the timer
    }

    for (auto it = agents.begin(); it != agents.end(); ) {
        Agent* agent = *it;
        agent->update();
        
        // Check if the agent should be removed
        if (!agent->is_alive() && !agent->is_player()) {
            it = agents.erase(it); // Remove from list and get the next iterator
            delete agent; // Free the memory
        } else {
            ++it; // Move to the next element
        }
    }

   // Find the player agent
    Agent* player = nullptr;
    for (auto agent : agents) {
        if (agent->is_player()) {
            player = agent;
            break;
        }
    }

    // Check for collisions between player and opponents
    if (player != nullptr) {
        for (auto agent : agents) {
            if (!agent->is_player() && checkCollision(player, agent)) {
                std::cout << "Collision!" << std::endl;
            } else {
                std::cout << std::endl;
            }
        }
    }

    // Update game state
    offset_y = std::fmod(offset_y + 64 - (256 * elapsedTime), 64);
}

void GameLoop::render() {
    // Clear off-screen canvas
    graphics.resetRendition();

    // Draw the grid on the off-screen canvas
    grid->drawGrid(graphics, *spriteSheet);

    // Copy a slice of the off-screen canvas back to itself to simulate scrolling
    graphics.scrollSlice((int)offset_x, (int)offset_y);

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
