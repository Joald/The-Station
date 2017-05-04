#pragma once
#include "The Station.h"

class explosion
{
    public:
        explosion(int x, int y, int lif);
        explosion(int x, int y);
        bool alive;
        void handle();
        int life;
        int state;
        sf::Sprite s;
};
