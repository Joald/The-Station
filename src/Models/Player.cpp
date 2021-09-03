#include "Player.h"

CollisionShape& Player::getCollisionShape() const {
    static CollisionCircle circle(getMiddle(), getTexture()->getSize().x);
    circle.moveTo(getMiddle());
    return circle;
}
