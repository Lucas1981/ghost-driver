#include "game-loop.h"
#include <iostream>

GameLoop::GameLoop() : offsetX(32.0), offsetY(0.0), createOpponentTimer(0.0) {}

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

        switch (gameState.getState()) {
            default:
                std::cerr << "Failed to initialize!" << std::endl;
                return;
            case GameStateType::TITLE_SCREEN:
                if (input.isKeyHeld(SDL_SCANCODE_RETURN)) {
                    gameState.setState(GameStateType::RUNNING);
                }
                titleScreen.drawTitleScreen(graphics.getRenderer());
                // ui.renderText(graphics.getRenderer(), "Greetings, earthling!", 200, 200);
                break;
            case GameStateType::RUNNING:
                play->run(true);
                break;
            case GameStateType::CRASHED:
                if (gameState.getTimeSinceLastStateChange() > 1) {
                    play->resetStage();
                    agents.clear();
                    agents.push_back(new Player(graphics.getRenderer(), spriteSheet, &input, &clock));
                    gameState.setState(GameStateType::RUNNING);
                }
                play->run(false);
                break;
        }

        graphics.present();
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
    play = new Play(graphics, clock, spriteSheet, grid, agents, gameState);
    if (!grid->loadGrid()) {
        std::cerr << "Failed to load grid!" << std::endl;
        return false;
    }

    // Load the title screen
    if (!titleScreen.loadTitleScreen(graphics.getRenderer(), "../assets/title-screen.png")) {
        std::cerr << "Failed to load title screen!" << std::endl;
        return false;
    }

    // Initialize the UI
    if (!ui.initialize(graphics.getRenderer(), "../assets/font.ttf", 24)) {
        std::cerr << "Failed to initialize UI!" << std::endl;
        return false;
    }
    
    return true;
}

void GameLoop::cleanup() {
    delete play;
    delete spriteSheet;
    delete grid;
    for (auto agent : agents) {
        delete agent;
    }
}
