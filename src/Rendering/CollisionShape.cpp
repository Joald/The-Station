#include "CollisionShape.h"
#include "Logging/Logger.h"

using STEngine::CollisionShape;
using STEngine::CollisionCircle;
using STEngine::CollisionRectangle;

bool CollisionShape::aABoundingBoxesCollide(const CollisionShape& other) const {
    auto boundingBox = getAABoundingBox();
    auto otherBoundingBox = other.getAABoundingBox();
    return !(boundingBox.rightLower().x < otherBoundingBox.leftUpper().x or
             boundingBox.rightLower().y < otherBoundingBox.leftUpper().y or
             boundingBox.leftUpper().x > otherBoundingBox.rightLower().x or
             boundingBox.leftUpper().y > otherBoundingBox.rightLower().y);
}

CollisionRectangle CollisionCircle::getAABoundingBox() const {
    return {origin - radius, origin + radius};
}

bool STEngine::CollisionCircle::internalCollidesWith(const CollisionRectangle& other) const {
    // defer to rectangle's implementation
    // careful not to call other.collidesWith(*this) which would cause infinite loop
    return collidesWith(other);
}

bool STEngine::CollisionCircle::internalCollidesWith(const CollisionCircle& other) const {
    return Math::distance(getOrigin(), other.getOrigin()) < getRadius() + other.getRadius();
}

bool STEngine::CollisionCircle::collidesWith(const CollisionShape& other) const {
    return other.collidesWith(*this);
}

bool STEngine::CollisionRectangle::internalCollidesWith(const CollisionCircle& other) const {
    const auto origin = other.getOrigin();
    auto radius = other.getRadius();

    for (const auto& vertex: vertices) {
        if (Math::distance(vertex, origin) < radius) {
            return true;
        }
    }
    for (int i = 0; i < vertices.size(); ++i) {
        const auto& v1 = vertices[i];
        const auto& v2 = vertices[(i + 1) % vertices.size()];
        if (Math::distanceFromLineSegment(origin, v1, v2) < radius) {
            return true;
        }
    }
    return false;
}

bool STEngine::CollisionRectangle::collidesWith(const CollisionShape& other) const {
    return other.internalCollidesWith(*this);
}

CollisionRectangle STEngine::CollisionRectangle::getAABoundingBox() const {
    if (isAxisAligned()) {
        return *this;
    }

    sf::Vector2f leftUpper(Math::minVector2f), rightLower(Math::maxVector2f);
    for (auto i: vertices) {
        leftUpper.x = std::min(leftUpper.x, i.x);
        leftUpper.y = std::min(leftUpper.y, i.y);
        rightLower.x = std::max(leftUpper.x, i.x);
        rightLower.y = std::max(leftUpper.y, i.y);
    }
    return {leftUpper, rightLower};
}

bool STEngine::CollisionRectangle::isAxisAligned() const {
    for (int i = 0; i < 4; ++i) {
        if (Math::areClose(rotation, Math::PI_2 * static_cast<float>(i))) {
            return true;
        }
    }
    return false;
}

const CollisionRectangle::SideLengths& STEngine::CollisionRectangle::getSideLengths() const {
    if (recomputeNeeded) {
        sides = recomputeSideLengths();
    }
    return sides;
}
