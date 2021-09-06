#include "CollisionCircle.h"


STEngine::CollisionRectangle STEngine::CollisionCircle::getAABoundingBox() const {
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