#ifndef THE_STATION_COLLIDABLE_H
#define THE_STATION_COLLIDABLE_H


#include "CollisionShape.h"

class Collidable {
    virtual CollisionShape& getCollisionShape() const = 0;

    bool collidesWith(const Collidable& other) {
        return getCollisionShape().collidesWith(other.getCollisionShape());
    }
};


#endif //THE_STATION_COLLIDABLE_H
