#include "../include/Projectile.h"

double Projectile::rotatexy(int mx, int my)          ///taking mouse coords for arguments
{
    double deltax, deltay, angle;                     ///double variables for calculation

    deltax = mx - this->x;                              ///delta n = objects position n - mouse pos n
    deltay = this->y - my;

    angle = (atan2(deltay, deltax)) * 180 / PI - 180;        /// trigonometry with arc tangent taking 2 args
    //angle=this->orig->orient;
    this->orient = angle;                             /// orient is a class angle variable

    this->C.setRotation(this->orig->C.getRotation() - 3);                 ///set rotation to object's sf::Sprite

    this->ay = sin(this->orient * PI / 180) * this->speed;
    this->ax = cos(this->orient * PI / 180) * this->speed;

    return this->orient;
}

void Projectile::setorig(Character *porig) {
    this->orig = porig;
    this->damage = porig->damage;
    this->x = porig->x;
    this->y = porig->y;
    this->wait = porig->shtdelay;
    //this->C.setOrigin(this->x,this->y);
    this->speed = porig->shtspeed;

}/*
Projectile::~Projectile()
{
    delete orig;
}*/

bool Projectile::canWalk(FloorTile floortile[n][m], Station &game) {
    int ox = this->x;
    int oy = this->y;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!floortile[i][j].walkable && ox > floortile[i][j].x && ox < floortile[i][j].x + 100 &&
                oy > floortile[i][j].y && oy < floortile[i][j].y + 104)
                return false;
        }
    }
    int fixw = 170;
    int fixh = 291;
    if (game.isUnsized) {
        fixw = 91;
        fixh = 155;
    }
    if (this->y > game.h - fixh + fixh * 2 / 5 || this->x > game.w - fixw - fixw / 20 || this->y < fixh ||
        this->x < fixw)
        return false;
    else
        return true;

}
