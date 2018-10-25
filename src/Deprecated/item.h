#pragma once

class item
{
    public:
        item(unsigned int id,int,int);
        item();
        ~item();
        unsigned int getId();
        int getType();
        int quant;
        int getEffectNum();
    protected:
    private:
        int effect;
        unsigned int id;
        int type;///0 - weapon 1 - medkit 2 - dmgboost
};
