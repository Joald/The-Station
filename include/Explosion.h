#ifndef THE_STATION_EXPLOSION_H
#define THE_STATION_EXPLOSION_H

#include "The_Station.h"

class Explosion
{
    public:
        Explosion(int x, int y, int lif);
        Explosion(int x, int y);
        bool alive;
        void handle();
        int life;
        int state;
        sf::Sprite s;
};

#endif //THE_STATION_EXPLOSION_H