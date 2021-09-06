#include "CollisionShape.h"
#include "Logging/Logger.h"
#include "CollisionRectangle.h"

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
