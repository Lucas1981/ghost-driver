#ifndef PLAY_H
#define PLAY_H

#include <list>  // for list
class Agent;
class Clock;
class GameState;
class Graphics;
class Grid;
class Sound;
class SpriteSheet;

class Play {
public:
    Play(
        Graphics& graphics,
        Clock& clock,
        SpriteSheet* spriteSheet,
        Grid* grid,
        std::list<Agent*>& agents,
        GameState& gameState,
        Sound& sound
    );
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
    Sound& sound;

    double createOpponentTimer;
    double offsetX;
    double offsetY;
};

#endif // PLAY_H
