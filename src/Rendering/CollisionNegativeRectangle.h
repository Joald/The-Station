#ifndef THE_STATION_COLLISIONNEGATIVERECTANGLE_H
#define THE_STATION_COLLISIONNEGATIVERECTANGLE_H

#include "CollisionShape.h"
#include "CollisionRectangle.h"

namespace STEngine {

class CollisionNegativeRectangle : public CollisionShape {
    CollisionRectangle rectangle;
public:
    explicit CollisionNegativeRectangle(CollisionRectangle rectangle) : rectangle(
            std::move(rectangle)) {}

private:
    bool internalCollidesWith(const CollisionRectangle& other) const override;

    bool internalCollidesWith(const CollisionCircle& other) const override;

    bool internalCollidesWith(const CollisionNegativeRectangle& other) const override;

public:
    bool collidesWith(const CollisionShape& other) const override;

    CollisionRectangle getAABoundingBox() const override;

};

}  // namespace STEngine

#endif //THE_STATION_COLLISIONNEGATIVERECTANGLE_H
