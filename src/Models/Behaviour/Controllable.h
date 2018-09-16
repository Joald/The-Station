#ifndef THE_STATION_CONTROLLABLE_H
#define THE_STATION_CONTROLLABLE_H


#include "../../Events/EventManager.h"
#include "../../Rendering/Renderer.h"
#include "../../Time/Time.h"

/**
 * Base class providing implementation of controllable entities.
 */
class Controllable : public virtual RenderableBase {
    float speed; /// In (scaled) pixels per second.
    bool controlled;

    void moveIfControlled(float x, float y) {
        if (controlled) {
            move(x, y);
        }
    }

    void getRegistered();

    float offset() {
        return speed * Time::deltaTime();
    }

protected:
    void setSpeed(float newSpeed) {
        Controllable::speed = newSpeed;
    }

    void toggleControlled() {
        Controllable::controlled = !controlled;
    }

    explicit Controllable(float speed, bool controlled = true) :
      speed(speed),
      controlled(controlled) {
        debugLog("Speed is ", speed);
        getRegistered();
    }

public:
    float getSpeed() const {
        return speed;
    }

    bool isControllable() const {
        return controlled;
    }
};


#endif //THE_STATION_CONTROLLABLE_H
