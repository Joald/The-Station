#ifndef THE_STATION_EVENT_MANAGER_H
#define THE_STATION_EVENT_MANAGER_H

#include <utility>
#include <functional>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "../Models/GameObject.h"
#include "EventContainer.h"


/**
 * Allows subtypes of GameObject to register for events and provide a
 * callback determining what to do. The callback should be a function taking
 * a reference to std::shared_ptr<Game_Object> and dynamic_pointer_cast it
 * to the appropriate derived type.
 */
class EventManager {
    template <class... Args>
    using CallbackSet = std::vector<std::function<void(Args...)>>;
    using GameObjectPtr = EventContainer::GameObjectPtr;
    using SfmlEventCallbackSet =
      std::map<sf::Event::EventType, CallbackSet<sf::Event>>;
    static SfmlEventCallbackSet sfmlEventCallbacks;
    static EventContainer events;
    static sf::Event sfmlEvent;
    static std::map<sf::Keyboard::Key, CallbackSet<>> keyHolds;
public:
    /**
     * When an SFML event is polled in a window, all callbacks registered with
     * this function are invoked.
     * @param caller - which object is listening
     * @param callback - function that performs the event handling
     */
    static void registerSfmlEvent(sf::Event::EventType eventType, std::function<void(sf::Event)> callback);

    /**
     * Runs the event loop for the given window and triggers all callbacks
     * registered for the appropriate event type.
     * Then, it checks all registered keys if they are being pressed and handles all
     * of them using registered callbacks.
     * @param window
     */
    static void triggerSfmlEvents(sf::RenderWindow& window);

    static void registerKeyHold(sf::Keyboard::Key, std::function<void()>);
};


#endif //THE_STATION_EVENT_MANAGER_H
