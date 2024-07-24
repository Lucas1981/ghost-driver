#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include <list>              // for list
#include "clock.h"           // for Clock
#include "graphics.h"        // for Graphics
#include "input.h"           // for Input
#include "sound.h"           // for Sound
#include "state.h"           // for GameState
#include "title-screen.h"    // for TitleScreen
#include "user-interface.h"  // for UI
class Agent;
class Grid;
class Play;
class SpriteSheet;

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
