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
        public STEngine::Collidable {

    sf::Vector2f getMiddle() const {
        return getPosition() + sf::Vector2f(getTexture()->getSize());
    }

public:
    Player();

    STEngine::CollisionShape& getCollisionShape() const override;
};


#endif //THE_STATION_PLAYER_H
