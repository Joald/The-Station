#ifndef THE_STATION_COLLIDABLE_H
#define THE_STATION_COLLIDABLE_H


#include "CollisionShape.h"
#include "CollisionDetector.h"

namespace STEngine {

class Collidable {
    [[nodiscard]] virtual CollisionShape& getCollisionShape() const = 0;

    bool collidesWith(const Collidable& other) {
        return getCollisionShape().collidesWith(other.getCollisionShape());
    }
};

} // STEngine

#endif //THE_STATION_COLLIDABLE_H
