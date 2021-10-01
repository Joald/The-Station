#ifndef THE_STATION_COLLIDABLE_H
#define THE_STATION_COLLIDABLE_H


#include "CollisionShape.h"
#include "CollisionDetector.h"

namespace STEngine {

class Collidable {
public:
    Collidable() = default;

    virtual ~Collidable() noexcept = default;

    Collidable(Collidable&&) = delete;

    Collidable(const Collidable&) = delete;

    Collidable& operator=(Collidable&&) = delete;

    Collidable& operator=(const Collidable&) = delete;

    [[nodiscard]] virtual const CollisionShape& getCollisionShape() const = 0;

    [[nodiscard]] bool collidesWith(const Collidable& other) const {
        return getCollisionShape().collidesWith(other.getCollisionShape());
    }
};

}  // namespace STEngine

#endif //THE_STATION_COLLIDABLE_H
