#ifndef CLOCK_H
#define CLOCK_H

#include <chrono>

class Clock {
public:
    Clock();
    void setTimer();
    double getElapsedTime() const;
    double getInitialTime() const;

private:
    using ClockType = std::chrono::steady_clock;
    ClockType::time_point initialTime;
    ClockType::time_point previousTime;
    ClockType::time_point currentTime;
};

#endif // CLOCK_H
