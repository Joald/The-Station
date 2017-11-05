#include "../include/TileDrop.h"

TileDrop::TileDrop(int xn,int yn,item col)
{
    this->collec.push_back(col);
    this->s.setPosition(xn-50,yn-23);
}
item TileDrop::collect()
{
    return collec[0];
}
