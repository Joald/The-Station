#pragma once
#include "The Station.h"
class item
{
    public:
        item(int id,int,int);
        item();
        ~item();
        int getId();
        int getType();
        int quant;
        int getEffectNum();
    protected:
    private:
        int effect;
        int id;
        int type;///0 - weapon 1 - medkit 2 - dmgboost
};
