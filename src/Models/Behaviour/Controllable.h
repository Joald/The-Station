#ifndef THE_STATION_CONTROLLABLE_H
#define THE_STATION_CONTROLLABLE_H


#include "Events/EventManager.h"
#include "Rendering/Renderer.h"
#include "Time/Time.h"

/**
 * Base class providing implementation of controllable entities.
 */
class Controllable : virtual GameObject {
    sf::Transformable& object;
    float speed; /// In (scaled) pixels per second.
    bool controlled;

    void moveIfControlled(float x, float y) {
        if (controlled) {
            object.move(x, y);
        }
    }

    void getRegistered();
    void getUnregistered();

    [[nodiscard]] float offset() const {
        return speed * Time::deltaTime();
    }

protected:
    void setSpeed(float newSpeed) {
        Controllable::speed = newSpeed;
    }

    void toggleControlled() {
        Controllable::controlled = !controlled;
    }

    explicit Controllable(sf::Transformable& object, float speed, bool controlled = true) :
            object(object),
            speed(speed),
            controlled(controlled) {
        getRegistered();
    }

public:
    virtual ~Controllable();

    [[nodiscard]] float getSpeed() const {
        return speed;
    }

    [[nodiscard]] bool isControllable() const {
        return controlled;
    }
};


#endif //THE_STATION_CONTROLLABLE_H
