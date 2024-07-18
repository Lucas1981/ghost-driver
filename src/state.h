#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <chrono>

enum class GameStateType {
    TITLE_SCREEN,
    RUNNING,
    CRASHED,
    GAME_OVER
};

class GameState {
public:
    GameState();

    // Getters
    GameStateType getState() const;
    std::chrono::steady_clock::time_point getLastStateChange() const;
    double getTimeLeft() const;
    double getDistanceTraveled() const;
    double getSpeed() const;
    double getTimeSinceLastStateChange() const; // New method

    // Setters
    void setState(GameStateType newState);
    void setTimeLeft(double timeLeft);
    void setDistanceTraveled(double distanceTraveled);
    void setSpeed(double speed);

private:
    GameStateType state;
    std::chrono::steady_clock::time_point lastStateChange;
    double timeLeft;
    double distanceTraveled;
    double speed;
};

#endif // GAME_STATE_H
