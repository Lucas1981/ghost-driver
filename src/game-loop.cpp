#include "game-loop.h"
#include <SDL_scancode.h>   // for SDL_SCANCODE_RETURN
#include <algorithm>        // for max
#include <cmath>            // for ceil
#include <iostream>         // for basic_ostream, operator<<, endl, cerr
#include <sstream>          // For std::stringstream
#include <string>           // for char_traits, allocator, basic_string
#include "agent.h"          // for Agent
#include "constants.h"      // for SCREEN_WIDTH
#include "grid.h"           // for Grid
#include "play.h"           // for Play
#include "player.h"         // for Player
#include "spritesheet.h"    // for SpriteSheet

using namespace Constants;

GameLoop::GameLoop() {}

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
                handleTitleScreenState();
                break;
            case GameStateType::READY:
                handleReadyState();
                break;
            case GameStateType::RUNNING:
                handleRunningState();
                break;
            case GameStateType::CRASHED:
                handleCrashedState();
                break;
            case GameStateType::TIME_UP:
                handleTimeUpState();
                break;
            case GameStateType::WIN:
                handleWinState();
                break;
        }

        sound.handleQueue();
        graphics.present();
    }
}

void GameLoop::handleTitleScreenState() {
    if (input.isKeyHeld(SDL_SCANCODE_RETURN)) {
        reset();
        gameState.setTimeLeft(60.0);
        gameState.setDistanceLeft(4.0);
        gameState.setSpeed(0);
        sound.enqueueSound(SoundType::START_ENGINE);
        gameState.setState(GameStateType::READY);
    }
    titleScreen.drawTitleScreen(graphics.getRenderer());
    ui.renderText(graphics.getRenderer(), "press enter to start", SCREEN_WIDTH / 2, 300, UI::TextAlign::CENTER);
}

void GameLoop::handleReadyState() {
    if (gameState.getTimeSinceLastStateChange() > 1) {
        gameState.setSpeed(255);
        gameState.setState(GameStateType::RUNNING);
    }
    play->run(false);
    displayStatus();
    ui.renderText(graphics.getRenderer(), "get ready!", SCREEN_WIDTH / 2, 200, UI::TextAlign::CENTER);
}

void GameLoop::handleRunningState() {
    gameState.reduceTimeLeft(clock.getElapsedTime());
    if (gameState.getTimeLeft() <= 0) {
        gameState.setTimeLeft(0);
        sound.enqueueSound(SoundType::LOST);
        gameState.setState(GameStateType::TIME_UP);
    }
    play->run(true);
    displayStatus();
}

void GameLoop::handleCrashedState() {
    gameState.reduceTimeLeft(clock.getElapsedTime());
    if (gameState.getTimeSinceLastStateChange() > 1) {
        reset();
        gameState.setSpeed(255);
        gameState.setState(GameStateType::RUNNING);
    }
    play->run(false);
    displayStatus();
}

void GameLoop::handleTimeUpState() {
    if (gameState.getTimeSinceLastStateChange() > 3) {
        gameState.setState(GameStateType::TITLE_SCREEN);        
    }
    play->run(false);
    displayStatus();
    ui.renderText(graphics.getRenderer(), "Time's up! You lost!", SCREEN_WIDTH / 2, 200, UI::TextAlign::CENTER);
}

void GameLoop::handleWinState() {
    if (gameState.getTimeSinceLastStateChange() > 2) {
        gameState.setState(GameStateType::TITLE_SCREEN);        
    }
    play->run(false);
    displayStatus();
    ui.renderText(graphics.getRenderer(), "Congratulations! You win!", SCREEN_WIDTH / 2, 200, UI::TextAlign::CENTER);
}

void GameLoop::reset() {
    play->resetStage();
    agents.clear();
    agents.push_back(new Player(spriteSheet, &input, &clock));
}

void GameLoop::displayStatus() {
    double roundedDownDistanceLeft = std::ceil(gameState.getDistanceLeft() * 10) / 10;
    double nonNegativeDistanceLeft = std::max(0.0, roundedDownDistanceLeft);
    std::stringstream speedString;
    std::stringstream timeLeftString;
    std::stringstream distanceLeftString;
    speedString << "speed: " << gameState.getSpeed(); 
    timeLeftString << "time: " << (int)gameState.getTimeLeft();
    distanceLeftString << "dist: " << nonNegativeDistanceLeft;
    ui.renderText(graphics.getRenderer(), speedString.str(), 0, 400, UI::TextAlign::LEFT);
    ui.renderText(graphics.getRenderer(), timeLeftString.str(), 0, 420, UI::TextAlign::LEFT);
    ui.renderText(graphics.getRenderer(), distanceLeftString.str(), 0, 440, UI::TextAlign::LEFT);
}

bool GameLoop::initialize() {
    if (!graphics.initialize()) {
        std::cerr << "Failed to initialize graphics!" << std::endl;
        return false;
    }
    spriteSheet = new SpriteSheet(graphics.getRenderer(), "../assets/tiles.png");
    agents.push_back(new Player(spriteSheet, &input, &clock));
    grid = new Grid("../assets/grid.txt", graphics, *spriteSheet);  // Initialize Grid with file path
    play = new Play(graphics, clock, spriteSheet, grid, agents, gameState, sound);
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
    if (!ui.initialize("../assets/font.ttf", 24)) {
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
