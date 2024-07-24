#include "play.h"
#include <cmath>            // for fmod
#include "agent.h"          // for Agent
#include "clock.h"          // for Clock
#include "collision.h"      // for checkCollision
#include "constants.h"      // for UNIT_SIZE
#include "graphics.h"       // for Graphics
#include "grid.h"           // for Grid
#include "opponent.h"       // for Opponent
#include "sound.h"          // for Sound, SoundType
#include "state.h"          // for GameState, GameStateType
class SpriteSheet;

Play::Play(
    Graphics& graphics,
    Clock& clock,
    SpriteSheet* spriteSheet,
    Grid* grid,
    std::list<Agent*>& agents,
    GameState& gameState,
    Sound& sound
) : graphics(graphics),
    clock(clock),
    spriteSheet(spriteSheet),
    grid(grid),
    agents(agents),
    gameState(gameState),
    sound(sound),
    createOpponentTimer(0.0),
    offsetX(32.0),
    offsetY(0.0) {}

Play::~Play() {
    // Destructor logic if needed
}
void Play::run(bool withUpdate) {
    if (withUpdate) {
        update();
    }
    render();
}

void Play::update() {
    using namespace Constants;

    double elapsedTime = clock.getElapsedTime();
    createOpponentTimer += elapsedTime;

    // Add a new opponent every 300 ms
    if (createOpponentTimer >= timeToNewOpponent) {
        agents.push_back(new Opponent(spriteSheet, &clock));
        createOpponentTimer = 0.0; // Reset the timer
    }

    for (auto it = agents.begin(); it != agents.end(); ) {
        Agent* agent = *it;
        agent->update();
        
        // Check if the agent should be removed
        if (!agent->isAlive() && !agent->isPlayer()) {
            it = agents.erase(it); // Remove from list and get the next iterator
            delete agent; // Free the memory
        } else {
            ++it; // Move to the next element
        }
    }

    // Find the player agent
    Agent* player = nullptr;
    for (auto agent : agents) {
        if (agent->isPlayer()) {
            player = agent;
            break;
        }
    }

    // Check for collisions between player and opponents
    if (player != nullptr) {
        for (auto agent : agents) {
            if (!agent->isPlayer() && checkCollision(player, agent)) {
                player->markAsCrashed();
                agent->markAsCrashed();
                gameState.setSpeed(0);
                sound.enqueueSound(SoundType::CRASH);
                gameState.setState(GameStateType::CRASHED);
            }
        }
    }

    double speedTimesElapsedTime = gameState.getSpeed() * elapsedTime;
    offsetY = std::fmod(offsetY + UNIT_SIZE - speedTimesElapsedTime, UNIT_SIZE);
    // Calculate the total distance we just traversed.
    // speed / hour * elapsedTime / meterPerHourConvertor
    double distanceTraveled = speedTimesElapsedTime * meterPerHourConvertor;
    gameState.reduceDistanceLeft(distanceTraveled);

    if (gameState.getDistanceLeft() <= 0.0) {
        sound.enqueueSound(SoundType::WON);
        gameState.setState(GameStateType::WIN);
    }
}

void Play::render() {
    // Clear off-screen canvas
    graphics.resetRendition();

    // Draw the grid on the off-screen canvas
    grid->drawGrid();

    // Copy a slice of the off-screen canvas back to itself to simulate scrolling
    graphics.scrollSlice((int)offsetX, (int)offsetY);

    // Draw all agents on the off-screen canvas
    for (auto agent : agents) {
        agent->draw(graphics); // No offset needed
    }
}

void Play::resetStage() {
    offsetY = 0;
}