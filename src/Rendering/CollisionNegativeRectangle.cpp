#include "CollisionNegativeRectangle.h"
#include "CollisionCircle.h"

bool STEngine::CollisionNegativeRectangle::internalCollidesWith(const STEngine::CollisionRectangle& other) const {
    return !other.isInside(rectangle);
}

bool STEngine::CollisionNegativeRectangle::internalCollidesWith(const CollisionCircle& other) const {
    const CollisionRectangle circleBound = other.getAABoundingBox();
    return !circleBound.isInside(rectangle);
}

bool STEngine::CollisionNegativeRectangle::collidesWith(const STEngine::CollisionShape& other) const {
    return other.collidesWith(*this);
}

STEngine::CollisionRectangle STEngine::CollisionNegativeRectangle::getAABoundingBox() const {
    constexpr auto infinity = std::numeric_limits<float>::infinity();
    return {sf::Vector2f(-infinity, -infinity), sf::Vector2f(infinity, infinity)};
}

bool STEngine::CollisionNegativeRectangle::internalCollidesWith(
        const STEngine::CollisionNegativeRectangle& other
) const {
    return true;
}
