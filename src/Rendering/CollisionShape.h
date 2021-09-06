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
    ), sides(recomputeSideLengths()),
    rotation(0) {}

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
    [[nodiscard]] bool internalCollidesWith(const CollisionRectangle& other) const override {
        bool boxesCollide = aABoundingBoxesCollide(other);
        if ((isAxisAligned() and other.isAxisAligned()) or !boxesCollide) {
            return boxesCollide;
        }
        // TODO: rotation?
        return false;
    }
    bool internalCollidesWith(const CollisionCircle& other) const override;
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

    bool collidesWith(const CollisionShape& other) const override;

protected:
    [[nodiscard]] bool internalCollidesWith(const CollisionCircle& other) const override;

protected:
    [[nodiscard]] bool internalCollidesWith(const CollisionRectangle& other) const override;
};

} // STEngine

#endif //THE_STATION_COLLISION_SHAPE_H
