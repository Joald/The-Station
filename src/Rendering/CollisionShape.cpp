#include "CollisionShape.h"
#include "CollisionRectangle.h"

using STEngine::CollisionShape;

bool CollisionShape::aABoundingBoxesCollide(const CollisionShape& other) const {
    const auto boundingBox = getAABoundingBox();
    const auto otherBoundingBox = other.getAABoundingBox();
    const bool xAxisNoOverlap =
            boundingBox.rightLower().x < otherBoundingBox.leftUpper().x
            or boundingBox.leftUpper().x > otherBoundingBox.rightLower().x;
    const bool yAxisNoOverlap =
            boundingBox.rightLower().y < otherBoundingBox.leftUpper().y or
            boundingBox.leftUpper().y > otherBoundingBox.rightLower().y;
    return !(xAxisNoOverlap or yAxisNoOverlap);
}

