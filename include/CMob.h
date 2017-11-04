#pragma once
#include "The Station.h"


#define n 16
#define m 6

class tile;
class Station;
class Room;
class item;
class CMob
{
public:
    sf::Sprite C;
    sf::Texture T;
    sf::Clock ifshot;
    bool red,invincible,isboss,isplayer;
    sf::Clock delay;
    //string name;
    int shtdelay;
    int health, speed, damage, armor,shtspeed, maxhp;
    double x,y,orient;
    int weaponiter;
    std::vector <item> inv;

    void addItem(item a);
    void addItem(int id,int type,int effect,int quantity);
    void useItem(int iter);
    void deleteItem(int iter,int quant);
    void DealDamage(int modifier);
    void toggleInvincible();
    void Heal(int modifier);
    void ModifySpeed(int modifier);
    void ModifyDamage(int modifier);
    void ModifyArmor(int modifier);
    virtual void rotatexy(int mx,int my);
    bool shoot(std::vector<projectile> &proj,int mx,int my);
    bool shoot(std::vector<projectile> &proj,int mx,int my,bool ignore);
    void rotate2mouse(Station& game);
    virtual bool canWalkUp(tile floortile[n][m],Station & game);
    virtual bool canWalkDown(tile floortile[n][m],Station & game);
    virtual bool canWalkRight(tile floortile[n][m],Station & game);
    virtual bool canWalkLeft(tile floortile[n][m],Station & game);
    CMob();
};
class enemy: public CMob
{
public:
    int ax, ay, destroystate,dir,type;
    sf::Clock destroyclock;
    void rotatexy(int mx,int my);
    bool canWalkUp(tile floortile[n][m],Station & game);
    bool canWalkDown(tile floortile[n][m],Station & game);
    bool canWalkRight(tile floortile[n][m],Station & game);
    bool canWalkLeft(tile floortile[n][m],Station & game);
    bool canSee(tile floortile[n][m],int x, int y);
    int returnpath(tile floortile[n][m],int x, int y);
    enemy();
};
class boss:public enemy
{
public:
    int phase,at2damage;
    boss();
};
