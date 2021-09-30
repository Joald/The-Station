#ifndef THE_STATION_COLLISION_SHAPE_H
#define THE_STATION_COLLISION_SHAPE_H

#include <array>
#include <SFML/System.hpp>
#include "Globals/Math.h"

namespace STEngine {

class CollisionRectangle;
class CollisionNegativeRectangle;
class CollisionCircle;

/**
 * Base class for abstract shapes that describe collisions.
 */
class CollisionShape {
protected:
    friend class CollisionRectangle;
    friend class CollisionCircle;

    [[nodiscard]] virtual bool internalCollidesWith(const CollisionRectangle& other) const = 0;
    [[nodiscard]] virtual bool internalCollidesWith(const CollisionCircle& other) const = 0;
    [[nodiscard]] virtual bool internalCollidesWith(const CollisionNegativeRectangle& other) const = 0;

public:
    [[nodiscard]] virtual CollisionRectangle getAABoundingBox() const = 0;
    [[nodiscard]] virtual bool collidesWith(const CollisionShape& other) const = 0;
    [[nodiscard]] bool aABoundingBoxesCollide(const CollisionShape& other) const;
};

}  // namespace STEngine

#endif //THE_STATION_COLLISION_SHAPE_H
