#include "Player.h"

const char PLAYER_TEXTURE_NAME[] = "Player";

CollisionShape& Player::getCollisionShape() const {
    static CollisionCircle circle(getMiddle(), getTexture()->getSize().x);
    circle.moveTo(getMiddle());
    return circle;
}
