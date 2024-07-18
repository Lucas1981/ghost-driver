#include "state.h"

GameState::GameState()
    : state(GameStateType::RUNNING),
      lastStateChange(std::chrono::steady_clock::now()),
      timeLeft(0.0),
      distanceTraveled(0.0),
      speed(0.0) {}

GameStateType GameState::getState() const {
    return state;
}

std::chrono::steady_clock::time_point GameState::getLastStateChange() const {
    return lastStateChange;
}

double GameState::getTimeLeft() const {
    return timeLeft;
}

double GameState::getDistanceTraveled() const {
    return distanceTraveled;
}

double GameState::getSpeed() const {
    return speed;
}

void GameState::setState(GameStateType newState) {
    state = newState;
    lastStateChange = std::chrono::steady_clock::now();
}

void GameState::setTimeLeft(double newTimeLeft) {
    timeLeft = newTimeLeft;
}

void GameState::setDistanceTraveled(double newDistanceTraveled) {
    distanceTraveled = newDistanceTraveled;
}

void GameState::setSpeed(double newSpeed) {
    speed = newSpeed;
}
