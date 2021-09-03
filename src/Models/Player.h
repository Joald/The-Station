#ifndef THE_STATION_PLAYER_H
#define THE_STATION_PLAYER_H


#include "GameObject.h"
#include "Rendering/Renderer.h"
#include "Behaviour/Controllable.h"
#include "Rendering/Collidable.h"

inline const std::string_view PLAYER_TEXTURE_NAME = "Player";

class Player :
        public GameObject,
        public Renderable,
        public Controllable,
        public Collidable {

    sf::Vector2f getMiddle() const {
        return getPosition() + sf::Vector2f(getTexture()->getSize());
    }

public:
    Player() :
            Renderable(PLAYER_TEXTURE_NAME, true),
            Controllable(*this, 100) {
        this->getShader().setUniform("texture", sf::Shader::CurrentTexture);
        debugAssert(getTexture()->getSize().x == getTexture()->getSize().y,
                    "X: " + std::to_string(getTexture()->getSize().x) + ", Y: " +
                    std::to_string(getTexture()->getSize().y));
    }

    CollisionShape& getCollisionShape() const override;
};


#endif //THE_STATION_PLAYER_H
