#ifndef THE_STATION_PLAYER_H
#define THE_STATION_PLAYER_H


#include "GameObject.h"
#include "../Rendering/Renderer.h"

extern const char PLAYER_TEXTURE_NAME[];

class Player : public GameObject, public Renderable<PLAYER_TEXTURE_NAME> {

};


#endif //THE_STATION_PLAYER_H
