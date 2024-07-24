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
#include "user-interface.h"
#include "sound.h"

class GameLoop {
public:
    GameLoop();
    ~GameLoop();
    void run();

private:
    bool initialize();
    void cleanup();
    void handleTitleScreenState();
    void handleReadyState();
    void handleRunningState();
    void handleCrashedState();
    void displayStatus();
    void handleTimeUpState();
    void handleWinState();
    void reset();

    GameState gameState;
    Graphics graphics;
    Clock clock;
    SpriteSheet* spriteSheet;
    Grid* grid;
    Input input;
    std::list<Agent*> agents;  // Use a list to store agents
    Play* play;
    TitleScreen titleScreen;
    UI ui;
    Sound sound;
};

#endif // GAME_LOOP_H
