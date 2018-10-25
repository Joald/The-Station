#ifndef THE_STATION_PROJECTILE_H
#define THE_STATION_PROJECTILE_H


#include <SFML/Graphics/Sprite.hpp>
#include "FloorTile.h"

#define n 16
#define m 6

class Character;

class FloorTile;

class GameState;

class Projectile {
public:
    int damage;
    int unsigned speed, wait, type;
    float x, y, ax, ay, orient;
    sf::Sprite C;

    Character *orig;

    void setorig(Character *orig);

    double rotatexy(float mx, float my);

    bool canWalk(FloorTile floortile[n][m], GameState &game);
    //Projectile();
    //~Projectile();
};

#endif
