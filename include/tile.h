#pragma once
#include "The Station.h"

class tile
{
public:
    sf::Sprite sprite;
    int x,y,type;///0 - floor, 1 - chest
    bool walkable;
};
