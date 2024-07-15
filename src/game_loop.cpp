#include "game_loop.h"
#include "collision.h"
#include <cmath> // Include the cmath header for std::fmod
#include <iostream>

GameLoop::GameLoop() : isRunning(true), gameState(GameState::TITLE_SCREEN), offset_x(32.0), offset_y(0.0), create_opponent_timer(0.0) {}

GameLoop::~GameLoop() {
    cleanup();
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

void GameLoop::handleEvents() {
    SDL_Event e;
    input.beginNewFrame();
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            isRunning = false;
        } else if (e.type == SDL_KEYDOWN) {
            if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                isRunning = false;
            }
            input.keyDownEvent(e);
        } else if (e.type == SDL_KEYUP) {
            input.keyUpEvent(e);
        }
    }
}

void GameLoop::update() {
    clock.setTimer();
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
    graphics.clear();
    grid->drawGrid(graphics, *spriteSheet);

    for (auto agent : agents) {
        agent->draw(graphics, (int)offset_x, (int)offset_y);
    }

    graphics.present((int)offset_x, (int)offset_y);
}

void GameLoop::cleanup() {
    delete spriteSheet;
    delete grid;
    for (auto agent : agents) {
        delete agent;
    }
}

void GameLoop::run() {
    if (!initialize()) {
        std::cerr << "Failed to initialize!" << std::endl;
        return;
    }

    while (isRunning) {
        handleEvents();
        update();
        render();
    }
}
