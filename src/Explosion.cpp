#include "../include/Explosion.h"

Explosion::Explosion(float x, float y, float life) {
    this->s.setPosition(x, y);
    this->life = life;
    this->state = 0;
    this->alive = true;
}

void Explosion::advance() {
    this->state++;
    if (this->state == this->life) {
        this->alive = false;
    }
}
