#include <SFML/Graphics/RenderWindow.hpp>
#include "EventManager.h"
#include "../Rendering/Renderer.h"

EventContainer EventManager::events;
sf::Event EventManager::sfml_event;

void EventManager::registerSFMLEvent(GameObjectPtr caller, std::function<void(GameObjectPtr, sf::Event&)> callback) {
    events.registerEvent(caller, GameEvent::SFML_EVENT, [&](GameObjectPtr& caller) { callback(caller, sfml_event); });
}

void EventManager::triggerSFMLEvents(sf::RenderWindow& window) {
    while (window.pollEvent(sfml_event)) {
        events.triggerEvent(GameEvent::SFML_EVENT);
    }
}
