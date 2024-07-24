#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <chrono>

enum class GameStateType {
    TITLE_SCREEN,
    READY,
    RUNNING,
    CRASHED,
    GAME_OVER,
    TIME_UP,
    WIN
};

class GameState {
public:
    GameState();

    // Getters
    GameStateType getState() const;
    std::chrono::steady_clock::time_point getLastStateChange() const;
    double getTimeLeft() const;
    double getDistanceLeft() const;
    double getSpeed() const;
    double getTimeSinceLastStateChange() const; // New method
    void reduceDistanceLeft(double distanceTraveled);
    void reduceTimeLeft(double elapsedTime);

    // Setters
    void setState(GameStateType newState);
    void setTimeLeft(double timeLeft);
    void setSpeed(double speed);
    void setDistanceLeft(double newDistanceLeft);

private:
    GameStateType state;
    std::chrono::steady_clock::time_point lastStateChange;
    double timeLeft;
    double distanceLeft;
    double speed;
};

#endif // GAME_STATE_H
