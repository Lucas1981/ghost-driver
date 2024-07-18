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
#include "state.h"
#include "play.h"
#include "title-screen.h"

class GameLoop {
public:
    GameLoop();
    ~GameLoop();
    void run();

private:
    bool initialize();
    void cleanup();

    GameState gameState;
    Graphics graphics;
    double offsetX;
    double offsetY;
    Clock clock;
    SpriteSheet* spriteSheet;
    Grid* grid;
    Player* player;
    Input input;
    std::list<Agent*> agents;  // Use a list to store agents
    Play* play;
    TitleScreen titleScreen;

    double createOpponentTimer; // Timer for creating new opponents
};

#endif // GAME_LOOP_H
