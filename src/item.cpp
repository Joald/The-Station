#include "../include/item.h"

item::item(int idx, int typex, int effectx) {
    this->id = idx;
    this->type = typex;
    this->effect = effectx;
    this->quant = 1;
}

item::~item() {
    //dtor
}

int item::getEffectNum() {
    return this->effect;
}

int item::getId() {
    return this->id;
}

int item::getType() {
    return this->type;
}

item::item() {
    this->id = 0;
    this->type = 0;
    this->effect = 30;
}
