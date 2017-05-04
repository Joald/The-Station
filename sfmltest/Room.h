


#pragma once
#include "The Station.h"

#define n 16
#define m 6
class Station;
class enemy;
class projectile;
class Room
{
public:
    tile floortile[n][m];
    sf::Texture floort,enemyt, sht,  chestt,dropst;
    sf::Image dli,dri,dti,dbi;
    int chest_max;
    int chestcount;
    int type;
    bool dleft, dright,dtop,dbottom,isempty;
    Room(Station&game);
    //void changeTo (const Room &ox, tile floortil[n][m] );


    std::vector<tiledrop> drops;
    std::vector <enemy> enem;
    std::vector <projectile> proj;
    void spawn_enemy(int x,int y,int typ);

    void spawnTiledrop(enemy& source);
};
