#ifndef AGENT_H
#define AGENT_H

#include <SDL2/SDL.h>
#include "graphics.h"

enum class State {
    ALIVE,
    DEAD
};

enum class Type {
    PLAYER,
    OPPONENT
};

class Agent {
public:
    virtual ~Agent() {}
    virtual void update() = 0;
    virtual void draw(Graphics& graphics) = 0;

    bool isAlive() const { return state == State::ALIVE; }
    bool isPlayer() const { return type == Type::PLAYER; }
    SDL_Rect getTranslatedHitbox() const; // Method to get translated hitbox

protected:
    int x, y;
    State state;
    Type type;
    SDL_Rect hitbox;
};

#endif // AGENT_H
