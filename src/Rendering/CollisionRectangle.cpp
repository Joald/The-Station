#include "CollisionRectangle.h"
#include "CollisionCircle.h"

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

STEngine::CollisionRectangle STEngine::CollisionRectangle::getAABoundingBox() const {
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

const STEngine::CollisionRectangle::SideLengths& STEngine::CollisionRectangle::getSideLengths() const {
    if (recomputeNeeded) {
        sides = recomputeSideLengths();
    }
    return sides;
}
