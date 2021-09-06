#include "CollisionShape.h"
#include "Logging/Logger.h"
#include "CollisionRectangle.h"

using STEngine::CollisionShape;

bool CollisionShape::aABoundingBoxesCollide(const CollisionShape& other) const {
    auto boundingBox = getAABoundingBox();
    auto otherBoundingBox = other.getAABoundingBox();
    return !(boundingBox.rightLower().x < otherBoundingBox.leftUpper().x or
             boundingBox.rightLower().y < otherBoundingBox.leftUpper().y or
             boundingBox.leftUpper().x > otherBoundingBox.rightLower().x or
             boundingBox.leftUpper().y > otherBoundingBox.rightLower().y);
}

