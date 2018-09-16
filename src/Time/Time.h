#ifndef THE_STATION_TIME_H
#define THE_STATION_TIME_H


#include <chrono>

class Time {
    using Clock = std::chrono::system_clock;
    static Clock::time_point previousFrame;
    static std::chrono::duration<float> timeSinceLastFrame;
public:
    static float deltaTime() {
        return timeSinceLastFrame.count();
    }

    static void update();
};


#endif //THE_STATION_TIME_H
