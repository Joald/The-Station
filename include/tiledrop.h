#pragma once
#include "The Station.h"

class item;
class tiledrop
{
public:
    tiledrop(int xn,int yn,item col);
    item collect();
    //void setCollect(item val);

    sf::Sprite s;
private:

    std::vector<item> collec;
};

