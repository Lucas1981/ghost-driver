#ifndef AGENT_H
#define AGENT_H

#include <SDL2/SDL.h>
#include "graphics.h"
#include "spritesheet.h"
#include "constants.h"

enum class AgentState {
    ALIVE,
    CRASHED,
    DEAD
};

enum class AgentType {
    PLAYER,
    OPPONENT
};

class Agent {
public:
    virtual ~Agent() {}
    virtual void update() = 0;
    virtual void draw(Graphics& graphics) = 0;

    void draw(Graphics& graphics, SpriteSheet* spriteSheet, TextureType type);
    bool isAlive() const { return state == AgentState::ALIVE; }
    bool isCrashed() const { return state == AgentState::CRASHED; }
    bool isPlayer() const { return type == AgentType::PLAYER; }
    void markAsCrashed() { state = AgentState::CRASHED; }
    SDL_Rect getTranslatedHitbox() const; // Method to get translated hitbox

protected:
    int x, y;
    AgentState state;
    AgentType type;
    SDL_Rect hitbox;
};

#endif // AGENT_H
