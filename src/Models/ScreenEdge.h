#ifndef THE_STATION_SCREENEDGE_H
#define THE_STATION_SCREENEDGE_H

#include <Rendering/Collidable.h>
#include <Rendering/CollisionNegativeRectangle.h>

class ScreenEdge : public STEngine::Collidable {
    STEngine::CollisionNegativeRectangle collision;
public:
    explicit ScreenEdge() : collision(STEngine::CollisionNegativeRectangle{STEngine::CollisionRectangle{{0.f, 0.f}, {1920.f, 1080.f}}}) {}
    [[nodiscard]] const STEngine::CollisionShape& getCollisionShape() const override;
};

#endif //THE_STATION_SCREENEDGE_H
