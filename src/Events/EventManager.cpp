#include <SFML/Graphics/RenderWindow.hpp>
#include "EventManager.h"
#include "../Rendering/Renderer.h"

EventContainer EventManager::events;
sf::Event EventManager::sfmlEvent;
EventManager::SfmlEventCallbackSet EventManager::sfmlEventCallbacks;
std::map<sf::Keyboard::Key, EventManager::CallbackSet<>> EventManager::keyHolds;

void EventManager::registerSfmlEvent(sf::Event::EventType eventType, std::function<void(sf::Event)> callback) {
    sfmlEventCallbacks[eventType].emplace_back(callback);
}

void EventManager::triggerSfmlEvents(sf::RenderWindow& window) {
    while (window.pollEvent(sfmlEvent)) {
        auto it = sfmlEventCallbacks.find(sfmlEvent.type);
        if (it != sfmlEventCallbacks.end()) {
            for (const auto& i : it->second) {
                i(sfmlEvent);
            }
        }
    }
    for (auto&[key, set] : keyHolds) {
        if (sf::Keyboard::isKeyPressed(key)) {
            for (auto& callback : set) {
                callback();
            }
        }
    }
}

void EventManager::registerKeyHold(sf::Keyboard::Key key, std::function<void()> callback) {
    keyHolds[key].emplace_back(callback);
}
