#include "Player.h"

STEngine::CollisionShape& Player::getCollisionShape() const {
    static STEngine::CollisionCircle circle(getMiddle(), static_cast<float>(getTexture()->getSize().x));
    circle.moveTo(getMiddle());
    return circle;
}
