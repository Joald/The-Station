#ifndef THE_STATION_TIME_H
#define THE_STATION_TIME_H


#include <chrono>

/**
 * Time utilities class.
 */
class Time {
    using Clock = std::chrono::system_clock;
    static Clock::time_point previousFrame;
    static std::chrono::duration<float> timeSinceLastFrame;
public:
    /**
     * @return time since the last frame in seconds.
     */
    static float deltaTime() {
        return timeSinceLastFrame.count();
    }

    /**
     * Register a new frame.
     */
    static void update();
};


#endif //THE_STATION_TIME_H
