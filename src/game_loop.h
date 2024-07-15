#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include <SDL2/SDL.h>
#include <list>
#include "graphics.h"
#include "clock.h"
#include "spritesheet.h"
#include "grid.h"
#include "input.h"
#include "player.h"
#include "opponent.h"

enum class GameState {
    TITLE_SCREEN,
    RUNNING
};

class GameLoop {
public:
    GameLoop();
    ~GameLoop();
    void run();

private:
    bool initialize();
    void handleEvents();
    void update();
    void render();
    void cleanup();

    bool isRunning;
    GameState gameState;
    Graphics graphics;
    double offset_x;
    double offset_y;
    Clock clock;
    SpriteSheet* spriteSheet;
    Grid* grid;
    Player* player;
    Input input;
    std::list<Agent*> agents;  // Use a list to store agents

    double create_opponent_timer; // Timer for creating new opponents
};

#endif // GAME_LOOP_H
