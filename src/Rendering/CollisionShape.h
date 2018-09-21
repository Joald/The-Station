#ifndef THE_STATION_COLLISION_SHAPE_H
#define THE_STATION_COLLISION_SHAPE_H

#include <array>
#include <SFML/System.hpp>
#include "../Globals/Math.h"

class Rectangle;

/**
 * Base class for abstract shapes that describe collisions.
 */
class CollisionShape {
protected:
    sf::Vector2f origin;
public:

    virtual bool collidesWith(const CollisionShape& other) const = 0;

    virtual Rectangle getBoundingBox() const = 0;

    bool boundingBoxesCollide(const CollisionShape& other) const;
};

class Rectangle : public CollisionShape {
    std::array<sf::Vector2f, 4> vertices;
    float rotation;
public:
    Rectangle(sf::Vector2f leftUpper, sf::Vector2f rightLower) : vertices(), rotation(0) {
        for (auto& i : vertices) {
            i = leftUpper;
        }
        vertices[1].x = rightLower.x;
        vertices[2] = rightLower;
        vertices[3].y = rightLower.y;
    }

    sf::Vector2f& leftUpper() {
        return vertices[0];
    }

    sf::Vector2f& rightLower() {
        return vertices[2];
    }

    bool collidesWith(const CollisionShape& other) const override {
        return false;
    }

    Rectangle getBoundingBox() const override {
        if (isAxisAligned()) {
            return *this;
        }

        sf::Vector2f leftUpper(minVector2f), rightLower(maxVector2f);
        for (auto i : vertices) {
            leftUpper.x = std::min(leftUpper.x, i.x);
            leftUpper.y = std::min(leftUpper.y, i.y);
            rightLower.x = std::max(leftUpper.x, i.x);
            rightLower.y = std::max(leftUpper.y, i.y);
        }
        return Rectangle(leftUpper, rightLower);
    }

    bool isAxisAligned() const {
        for (int i = 0; i < 4; ++i) {
            if (areClose(rotation, PI_2 * i)) {
                return true;
            }
        }
        return false;
    }

    bool collidesWith(const Rectangle& other) const {
        bool boxesCollide = boundingBoxesCollide(other);
        if ((isAxisAligned() and other.isAxisAligned()) or !boxesCollide) {
            return boxesCollide;
        }

    }
};

class Circle : public CollisionShape {
    float radius;
public:
    bool collidesWith(const CollisionShape& other) const override;

    Rectangle getBoundingBox() const override;
};

#endif //THE_STATION_COLLISION_SHAPE_H
