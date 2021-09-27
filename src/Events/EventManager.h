#ifndef THE_STATION_EVENT_MANAGER_H
#define THE_STATION_EVENT_MANAGER_H

#include <utility>
#include <functional>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <map>
#include "Models/GameObject.h"


/**
 * Allows subtypes of GameObject to register for events and provide a
 * callback determining what to do. The callback should be a function taking
 * a reference to std::shared_ptr<GameObject> and dynamic_pointer_cast it
 * to the appropriate derived type.
 */
class EventManager {
    template <class... Args>
    using CallbackSet = std::vector<std::function<void(Args...)>>;
    using SfmlEventCallbackSet =
      std::map<sf::Event::EventType, CallbackSet<sf::Event>>;
    inline static SfmlEventCallbackSet sfmlEventCallbacks;
    inline static sf::Event sfmlEvent;
    inline static std::map<sf::Keyboard::Key, CallbackSet<>> keyHolds;
public:
    /**
     * When an SFML event of the specified type is polled in a window,
     * all callbacks registered with this function are invoked.
     * @param eventType - type of event
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


    /**
     * Register a callback to be called every frame if the specified key is pressed.
     * The callbacks will be called after the event loop in @triggerSfmlEvents.
     */
    static void registerKeyHold(sf::Keyboard::Key, std::function<void()>);
};


#endif //THE_STATION_EVENT_MANAGER_H
