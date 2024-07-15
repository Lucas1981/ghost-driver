#include "clock.h"

Clock::Clock() {
    initialTime = ClockType::now();
    previousTime = initialTime;
    currentTime = initialTime;
}

void Clock::setTimer() {
    previousTime = currentTime;
    currentTime = ClockType::now();
}

double Clock::getElapsedTime() const {
    using namespace std::chrono;
    return duration_cast<duration<double>>(currentTime - previousTime).count();
}

double Clock::getInitialTime() const {
    using namespace std::chrono;
    return duration_cast<duration<double>>(ClockType::now() - initialTime).count();
}
