#pragma once

#include "The_Station.h"


#define n 16
#define m 6

class FloorTile;

class Station;

class Room;

class item;

class Character : public sf::Sprite {
public:
    sf::Clock ifshot;
    bool red, invincible;
    sf::Clock delay;
    //string name;
    unsigned int shtspeed, shtdelay;
    int health, speed, damage, armor, maxhp;
    float /*x, y,*/ orient;
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

    void rotatexy(sf::Vector2f vector2f);
    void rotatexy(sf::Vector2i vector2i);

    bool shoot(std::vector<Projectile> &proj, float mx, float my);
    bool shoot(std::vector<Projectile> &proj, sf::Vector2f vector2f);

    bool shoot(std::vector<Projectile> &proj, int mx, int my, bool ignore);

    void rotate2mouse(Station &game);

    virtual bool canWalkUp(FloorTile floortile[n][m], Station &game);

    virtual bool canWalkDown(FloorTile floortile[n][m], Station &game);

    virtual bool canWalkRight(FloorTile floortile[n][m], Station &game);

    virtual bool canWalkLeft(FloorTile floortile[n][m], Station &game);

    Character();

    int x_int() {
        return static_cast<int>(getPosition().x);
    }
    int y_int() {
        return static_cast<int>(getPosition().y);
    }

protected:
    virtual void rotatexy_internal(float mouseX, float mouseY);
};

class enemy : public Character {
public:
    int destroystate, dir, type;
    float ax, ay;
    sf::Clock destroyClock;

    bool canWalkUp(FloorTile floortile[n][m], Station &game) override;

    bool canWalkDown(FloorTile floortile[n][m], Station &game) override;

    bool canWalkRight(FloorTile floortile[n][m], Station &game) override;

    bool canWalkLeft(FloorTile floortile[n][m], Station &game) override;

    bool canSee(FloorTile floortile[n][m], float x, float y);
    bool canSee(FloorTile floortile[n][m], sf::Vector2f v);
    int returnpath(FloorTile floortile[n][m], float x, float y);
    int returnpath(FloorTile floortile[n][m], sf::Vector2f vector2f);

    enemy();

protected:
    void rotatexy_internal(float mouseX, float mouseY) override;
};

class boss : public enemy {
public:
    int phase, at2damage;

    boss();
};
