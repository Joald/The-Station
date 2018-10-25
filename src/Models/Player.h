#ifndef THE_STATION_PLAYER_H
#define THE_STATION_PLAYER_H


#include "GameObject.h"
#include "../Rendering/Renderer.h"
#include "Behaviour/Controllable.h"
#include "../Rendering/Collidable.h"

extern const char PLAYER_TEXTURE_NAME[];

class Player :
  public GameObject,
  public virtual Renderable<PLAYER_TEXTURE_NAME, true>,
  public virtual Controllable,
  public Collidable {
    sf::Vector2f getMiddle() const {
        return getPosition() + sf::Vector2f(getTexture()->getSize());
    }
public:
    Player(): Controllable(100) {
        getShader()->setUniform("texture", sf::Shader::CurrentTexture);
        debugAssert(getTexture()->getSize().x == getTexture()->getSize().y,
                "X: " + std::to_string(getTexture()->getSize().x) + ", Y: " + std::to_string(getTexture()->getSize().y));
    }

    CollisionShape& getCollisionShape() const override;
};


#endif //THE_STATION_PLAYER_H
