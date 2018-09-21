#include "CollisionShape.h"

bool CollisionShape::boundingBoxesCollide(const CollisionShape& other) const {
    auto boundingBox = getBoundingBox();
    auto otherBoundingBox = other.getBoundingBox();
    return
      !(boundingBox.rightLower().x < otherBoundingBox.leftUpper().x or
        boundingBox.rightLower().y < otherBoundingBox.leftUpper().y or
        boundingBox.leftUpper().x > otherBoundingBox.rightLower().x or
        boundingBox.leftUpper().y > otherBoundingBox.rightLower().y);
}

bool Circle::collidesWith(const CollisionShape& other) const {
    debugLog("bool Circle::collidesWith(const CollisionShape& other) not implemented!");
    return false;
}

Rectangle Circle::getBoundingBox() const {
    return Rectangle(origin - radius, origin + radius);
}
