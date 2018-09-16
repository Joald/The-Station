#include "Time.h"

Time::Clock::time_point Time::previousFrame = Time::Clock::now();
std::chrono::duration<float> Time::timeSinceLastFrame;

void Time::update() {
    auto now = Clock::now();
    timeSinceLastFrame = now - previousFrame;
    previousFrame = now;
}
