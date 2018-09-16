#include "Controllable.h"

void Controllable::getRegistered() {
    EventManager::registerKeyHold(sf::Keyboard::W, [&] {
        moveIfControlled(0, -offset());
    });
    EventManager::registerKeyHold(sf::Keyboard::S, [&] {
        moveIfControlled(0, offset());
    });
    EventManager::registerKeyHold(sf::Keyboard::A, [&] {
        moveIfControlled(-offset(), 0);
    });
    EventManager::registerKeyHold(sf::Keyboard::D, [&] {
        moveIfControlled(offset(), 0);
    });
}
