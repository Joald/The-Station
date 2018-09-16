#ifndef THE_STATION_PLAYER_H
#define THE_STATION_PLAYER_H


#include "GameObject.h"
#include "../Rendering/Renderer.h"
#include "Behaviour/Controllable.h"

extern const char PLAYER_TEXTURE_NAME[];

class Player :
  public GameObject,
  public virtual Renderable<PLAYER_TEXTURE_NAME, true>,
  public virtual Controllable {
public:
    Player(): Controllable(100) {
        getShader()->setUniform("texture", sf::Shader::CurrentTexture);
    }
};


#endif //THE_STATION_PLAYER_H
