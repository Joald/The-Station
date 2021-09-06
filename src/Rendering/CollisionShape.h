#ifndef THE_STATION_COLLISION_SHAPE_H
#define THE_STATION_COLLISION_SHAPE_H

#include <array>
#include <SFML/System.hpp>
#include "Globals/Math.h"

namespace STEngine {

class CollisionRectangle;

class CollisionCircle;

/**
 * Base class for abstract shapes that describe collisions.
 */
class CollisionShape {
protected:
    friend class CollisionRectangle;
    friend class CollisionCircle;
    sf::Vector2f origin;
    [[nodiscard]] virtual bool internalCollidesWith(const CollisionRectangle& other) const = 0;

    [[nodiscard]] virtual bool internalCollidesWith(const CollisionCircle& other) const = 0;

public:
    [[nodiscard]] virtual CollisionRectangle getAABoundingBox() const = 0;
    [[nodiscard]] virtual bool collidesWith(const CollisionShape& other) const = 0;
    [[nodiscard]] bool aABoundingBoxesCollide(const CollisionShape& other) const;
};

class CollisionCircle : public CollisionShape {
    sf::Vector2f origin;
    float radius;
public:
    explicit CollisionCircle(sf::Vector2f origin, float radius) : origin(origin), radius(radius) {}

    void moveTo(sf::Vector2f newOrigin) {
        origin = newOrigin;
    }

    [[nodiscard]] CollisionRectangle getAABoundingBox() const override;

    [[nodiscard]] sf::Vector2f getOrigin() const {
        return origin;
    }

    [[nodiscard]] float getRadius() const {
        return radius;
    }

    [[nodiscard]] bool collidesWith(const CollisionShape& other) const override;

protected:
    [[nodiscard]] bool internalCollidesWith(const CollisionCircle& other) const override;

protected:
    [[nodiscard]] bool internalCollidesWith(const CollisionRectangle& other) const override;
};

} // STEngine

#endif //THE_STATION_COLLISION_SHAPE_H
