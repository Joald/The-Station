#include "Controllable.h"

void Controllable::getRegistered() {
    eventManager().registerKeyHold(generateID("W"), sf::Keyboard::W, [&] {
        moveIfControlled(0, -offset());
    });
    eventManager().registerKeyHold(generateID("S"), sf::Keyboard::S, [&] {
        moveIfControlled(0, offset());
    });
    eventManager().registerKeyHold(generateID("A"), sf::Keyboard::A, [&] {
        moveIfControlled(-offset(), 0);
    });
    eventManager().registerKeyHold(generateID("D"), sf::Keyboard::D, [&] {
        moveIfControlled(offset(), 0);
    });
}

void Controllable::getUnregistered() {
    for (const auto& key : std::array<const char*, 4>{"W", "S", "A", "D"}) {
        eventManager().unregisterEvent(generateID(key));
    }
}

Controllable::~Controllable() {
    getUnregistered();
}
