#include "CollisionRectangle.h"
#include "CollisionCircle.h"
#include "CollisionNegativeRectangle.h"

namespace stdr = std::ranges;

bool STEngine::CollisionRectangle::internalCollidesWith(const CollisionCircle& other) const {
    const auto origin = other.getOrigin();
    auto radius = other.getRadius();
    auto distances = std::array<float, 4>{};
    std::transform(vertices.begin(), vertices.end(), distances.begin(), [=](const sf::Vector2f& vertex) {
        return Math::distance(vertex, origin);
    });

    if (stdr::any_of(distances, [=](float dist) { return dist < radius; })) {
        return true;
    }

    // TODO: check if heuristics improve speed
    // TODO: add heuristic that returns false if all vertices are further away
    //  from origin than longest side

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

    sf::Vector2f leftUpper = Math::minVector2f;
    sf::Vector2f rightLower = Math::maxVector2f;
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

bool STEngine::CollisionRectangle::internalCollidesWith(const STEngine::CollisionRectangle& other) const {
    bool boxesCollide = aABoundingBoxesCollide(other);
    if ((isAxisAligned() and other.isAxisAligned()) or !boxesCollide) {
        return boxesCollide;
    }
    // TODO: rotation?
    return false;
}

bool STEngine::CollisionRectangle::isInside(const STEngine::CollisionRectangle& other) const {
    const bool xAxisInside =
            other.leftUpper().x < leftUpper().x
            and rightLower().x < other.rightLower().x;
    const bool yAxisInside =
            other.leftUpper().y < leftUpper().y
            and rightLower().y < other.rightLower().y;
    return xAxisInside and yAxisInside;
}

bool STEngine::CollisionRectangle::internalCollidesWith(const CollisionNegativeRectangle& other) const {
    return other.collidesWith(*this);
}
