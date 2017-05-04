#include "The Station.h"

tiledrop::tiledrop(int xn,int yn,item col)
{
    this->collec.push_back(col);
    this->s.setPosition(xn-50,yn-23);
}
item tiledrop::collect()
{
    return collec[0];
}
