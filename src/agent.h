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
    virtual void draw(Graphics& graphics, int offset_x, int offset_y) = 0;

    bool is_alive() const { return state == State::ALIVE; }
    bool is_player() const { return type == Type::PLAYER; }
    SDL_Rect get_translated_hitbox() const; // Method to get translated hitbox

protected:
    int x, y;
    State state;
    Type type;
    SDL_Rect hitbox;
};

#endif // AGENT_H
