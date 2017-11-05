#pragma once

#include "The_Station.h"


#define n 16
#define m 6

class FloorTile;

class Station;

class Room;

class item;

class Character {
public:
    sf::Sprite C;
    sf::Texture T;
    sf::Clock ifshot;
    bool red, invincible, isboss, isplayer;
    sf::Clock delay;
    //string name;
    int shtdelay;
    int health, speed, damage, armor, shtspeed, maxhp;
    double x, y, orient;
    int weaponiter;
    std::vector<item> inv;

    void addItem(item a);

    void addItem(int id, int type, int effect, int quantity);

    void useItem(int iter);

    void deleteItem(int iter, int quant);

    void DealDamage(int modifier);

    void toggleInvincible();

    void Heal(int modifier);

    void ModifySpeed(int modifier);

    void ModifyDamage(int modifier);

    void ModifyArmor(int modifier);

    virtual void rotatexy(int mx, int my);

    bool shoot(std::vector<Projectile> &proj, int mx, int my);

    bool shoot(std::vector<Projectile> &proj, int mx, int my, bool ignore);

    void rotate2mouse(Station &game);

    virtual bool canWalkUp(FloorTile floortile[n][m], Station &game);

    virtual bool canWalkDown(FloorTile floortile[n][m], Station &game);

    virtual bool canWalkRight(FloorTile floortile[n][m], Station &game);

    virtual bool canWalkLeft(FloorTile floortile[n][m], Station &game);

    Character();
};

class enemy : public Character {
public:
    int ax, ay, destroystate, dir, type;
    sf::Clock destroyclock;

    void rotatexy(int mx, int my);

    bool canWalkUp(FloorTile floortile[n][m], Station &game);

    bool canWalkDown(FloorTile floortile[n][m], Station &game);

    bool canWalkRight(FloorTile floortile[n][m], Station &game);

    bool canWalkLeft(FloorTile floortile[n][m], Station &game);

    bool canSee(FloorTile floortile[n][m], int x, int y);

    int returnpath(FloorTile floortile[n][m], int x, int y);

    enemy();
};

class boss : public enemy {
public:
    int phase, at2damage;

    boss();
};
