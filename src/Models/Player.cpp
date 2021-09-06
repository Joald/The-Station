#include "Player.h"

STEngine::CollisionShape& Player::getCollisionShape() const {
    static STEngine::CollisionCircle circle(getMiddle(), static_cast<float>(getTexture()->getSize().x));
    circle.moveTo(getMiddle());
    return circle;
}

Player::Player() :
        GameObject("player"),
        Renderable(PLAYER_TEXTURE_NAME, true),
        Controllable(*this, 100) {
    this->getShader().setUniform("texture", sf::Shader::CurrentTexture);
    debugAssert(getTexture()->getSize().x == getTexture()->getSize().y,
                "X: " + std::to_string(getTexture()->getSize().x) + ", Y: " +
                std::to_string(getTexture()->getSize().y));
}
