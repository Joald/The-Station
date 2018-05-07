#ifndef FLOOR_TILE_H
#define FLOOR_TILE_H

#include "The_Station.h"

class FloorTile {
public:
    sf::Sprite sprite;
    int x, y, type;///0 - floor, 1 - chest
    bool walkable;
};

#endif //FLOOR_TILE_H