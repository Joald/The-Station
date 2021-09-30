#ifndef THE_STATION_COLLISIONRECTANGLE_H
#define THE_STATION_COLLISIONRECTANGLE_H

#include "CollisionShape.h"

namespace STEngine {

// Rectangle is filled
class CollisionRectangle : public CollisionShape {
    using Vertices = std::array<sf::Vector2f, 4>;
    using SideLengths = std::array<float, 4>;
    mutable SideLengths sides;
    Vertices vertices;
    float rotation;
    bool recomputeNeeded = false;
public:
    CollisionRectangle(sf::Vector2f leftUpper, sf::Vector2f rightLower) : vertices(
            {leftUpper, {rightLower.x, leftUpper.y}, rightLower, {leftUpper.x, rightLower.y}}
    ), sides(recomputeSideLengths()), rotation(0) {}

    [[nodiscard]] const sf::Vector2f& leftUpper() const {
        return vertices[0];
    }

    [[nodiscard]] const sf::Vector2f& rightLower() const {
        return vertices[2];
    }

    [[nodiscard]] CollisionRectangle getAABoundingBox() const override;

    [[nodiscard]] bool isAxisAligned() const;

    [[nodiscard]] const SideLengths& getSideLengths() const;

    [[nodiscard]] const Vertices& getVertices() const {
        return vertices;
    }

    bool collidesWith(const CollisionShape& other) const override;

    bool isInside(const CollisionRectangle& other) const;

private:
    [[nodiscard]] SideLengths recomputeSideLengths() const {
        return {
                Math::distance(vertices[0], vertices[1]),
                Math::distance(vertices[1], vertices[2]),
                Math::distance(vertices[2], vertices[3]),
                Math::distance(vertices[3], vertices[0]),
        };
    }

protected:
    [[nodiscard]] bool internalCollidesWith(const CollisionRectangle& other) const override;

    bool internalCollidesWith(const CollisionCircle& other) const override;

    bool internalCollidesWith(const CollisionNegativeRectangle& other) const override;
};

}  // namespace STEngine

#endif //THE_STATION_COLLISIONRECTANGLE_H
