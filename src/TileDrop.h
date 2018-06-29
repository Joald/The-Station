#ifndef TILE_DROP_H
#define TILE_DROP_H


#include <SFML/Graphics.hpp>
#include <vector>
#include "item.h"

class item;

class TileDrop {
public:
    TileDrop(int xn, int yn, item col);

    item collect();
    //void setCollect(item val);

    sf::Sprite s;
private:

    std::vector<item> collec;
};

#endif // TILE_DROP_H