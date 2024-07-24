#ifndef PLAY_H
#define PLAY_H

#include <list>
#include "graphics.h"
#include "clock.h"
#include "spritesheet.h"
#include "grid.h"
#include "agent.h"
#include "input.h"
#include "opponent.h"
#include "state.h"

class Play {
public:
    Play(Graphics& graphics, Clock& clock, SpriteSheet* spriteSheet, Grid* grid, std::list<Agent*>& agents, GameState& gameState);
    ~Play();

    void run(bool withUpdate);
    void resetStage();

private:
    void update();
    void render();

    static constexpr double meterPerHourConvertor = 0.000277;
    static constexpr double timeToNewOpponent = 0.24;
    Graphics& graphics;
    Clock& clock;
    SpriteSheet* spriteSheet;
    Grid* grid;
    std::list<Agent*>& agents;
    GameState& gameState;

    double createOpponentTimer;
    double offsetX;
    double offsetY;
};

#endif // PLAY_H
