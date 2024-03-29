#ifndef THE_STATION_EXPLOSION_H
#define THE_STATION_EXPLOSION_H

#include <SFML/Graphics/Sprite.hpp>

class Explosion
{
    public:
        Explosion(float x, float y, float life = 9);
        bool alive;
        void advance();
        float life;
        int state;
        sf::Sprite s;
};

#endif //THE_STATION_EXPLOSION_H