#include "../include/Explosion.h"

Explosion::Explosion(int x, int y, int lif) {
    //ctor
    this->s.setPosition(x, y);
    this->life = lif;
    this->state = 0;
    this->alive = true;
}

Explosion::Explosion(int x, int y) {
    //ctor
    this->s.setPosition(x, y);
    this->life = 9;
    this->state = 0;
    this->alive = true;
}

void Explosion::handle() {

    this->state++;
    if (this->state == this->life) {
        this->alive = false;
    }
}
