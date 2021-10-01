#ifndef THE_STATION_EVENT_MANAGER_H
#define THE_STATION_EVENT_MANAGER_H

#include <string_view>
#include <functional>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <any>
#include "Models/GameObject.h"

/**
 * Allows subtypes of GameObject to register for events and provide a
 * callback determining what to do. The callback should be a function taking
 * a reference to std::shared_ptr<GameObject> and dynamic_pointer_cast it
 * to the appropriate derived type.
 */
class EventManager {
protected:
    constexpr EventManager() noexcept = default;
public:
    virtual ~EventManager() noexcept = default;

    EventManager(EventManager&&) = delete;

    EventManager(const EventManager&) = delete;

    EventManager& operator=(EventManager&&) = delete;

    EventManager& operator=(const EventManager&) = delete;

    /**
     * When an SFML event of the specified type is polled in a window,
     * all callbacks registered with this function are invoked.
     * @param eventType - type of event
     * @param callback - function that performs the event handling
     */
    virtual void registerSfmlEvent(std::string_view id, sf::Event::EventType eventType,
                                   std::function<void(sf::Event)> callback) = 0;

    /**
     * Runs the event loop for the given window and triggers all callbacks
     * registered for the appropriate event type.
     * Then, it checks all registered keys if they are being pressed and handles all
     * of them using registered callbacks.
     * @param window
     */
    virtual void triggerSfmlEvents(sf::RenderWindow& window) = 0;


    /**
     * Register a callback to be called every frame if the specified key is pressed.
     * The callbacks will be called after the event loop in @triggerSfmlEvents.
     */
    virtual void registerKeyHold(std::string_view id, sf::Keyboard::Key key,
                                 std::function<void()> callback) = 0;


    /**
     * Override the callback for an event registered using the ID.
     * @param id
     * @param callback must be of the same type as the original callback
     */
    virtual void changeEvent(std::string_view id, std::any callback) = 0;

    /**
     * Unregister an event. Expensive operation, O(n) where n is the number
     * of events triggered at the same time.
     * @param id
     */
    virtual void unregisterEvent(std::string_view id) = 0;
};

EventManager& eventManager();

#endif //THE_STATION_EVENT_MANAGER_H
