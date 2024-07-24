#include "state.h"

GameState::GameState()
    : state(GameStateType::TITLE_SCREEN),
      lastStateChange(std::chrono::steady_clock::now()),
      timeLeft(0.0),
      distanceLeft(0.0),
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

double GameState::getDistanceLeft() const {
    return distanceLeft;
}

double GameState::getSpeed() const {
    return speed;
}

double GameState::getTimeSinceLastStateChange() const {
    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = now - lastStateChange;
    return elapsed_seconds.count();
}

void GameState::setState(GameStateType newState) {
    state = newState;
    lastStateChange = std::chrono::steady_clock::now();
}

void GameState::setDistanceLeft(double newDistanceLeft) {
    distanceLeft = newDistanceLeft;
}

void GameState::setTimeLeft(double newTimeLeft) {
    timeLeft = newTimeLeft;
}

void GameState::reduceDistanceLeft(double distanceTraveled) {
    distanceLeft -= distanceTraveled;
}

void GameState::reduceTimeLeft(double elapsedTime) {
    timeLeft -= elapsedTime;
}

void GameState::setSpeed(double newSpeed) {
    speed = newSpeed;
}
