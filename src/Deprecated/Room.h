#ifndef ROOM_H
#define ROOM_H

#include <SFML/Graphics.hpp>

#include "FloorTile.h"

#define n 16
#define m 6

class GameState;

class enemy;

class Projectile;

class FloorTile;

class TileDrop;

class Room {
public:
    FloorTile floortile[n][m];
    sf::Texture floort, enemyt, sht, chestt, dropst;
    sf::Image dli, dri, dti, dbi;
    int chest_max;
    int chestcount;
    int type;
    bool dleft, dright, dtop, dbottom, isempty;

    explicit Room(GameState &game);
    //void changeTo (const Room &ox, FloorTile floortil[n][m] );


    std::vector<TileDrop> drops;
    std::vector<enemy> enem;
    std::vector<Projectile> proj;

    void spawn_enemy(float x, float y, int type);

    void spawnTiledrop(enemy &source);
};

#endif //ROOM_H