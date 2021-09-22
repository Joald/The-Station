#ifndef THE_STATION_COLLISIONCIRCLE_H
#define THE_STATION_COLLISIONCIRCLE_H


#include "CollisionRectangle.h"
#include "CollisionShape.h"

namespace STEngine {

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

    bool internalCollidesWith(const CollisionNegativeRectangle& other) const override;
};

}

#endif //THE_STATION_COLLISIONCIRCLE_H
