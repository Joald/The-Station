#pragma once
#include "The Station.h"

#define n 16
#define m 6

class CMob;
class tile;
class Station;

class projectile
{
public:
    int damage;
    int unsigned  speed,wait,type;
    double  x,y,ax,ay,orient;
    sf::Sprite C;

    CMob *orig;
    void setorig(CMob *orig);
    double rotatexy(int mx,int my);
    bool canWalk(tile floortile[n][m],Station & game);
    //projectile();
    //~projectile();
};

//class bossprojectile
