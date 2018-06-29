#ifndef THE_STATION_EVENTMANAGER_H
#define THE_STATION_EVENTMANAGER_H

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
    static EventContainer events;
    static sf::Event sfml_event;
    using GameObjectPtr = EventContainer::GameObjectPtr;
public:
    /**
     * When an SFML event is polled in a window, all callbacks registered with
     * this function are invoked. Every callback must check if the event passed
     * to the callback is of appropriate type.
     * @param caller - which object is listening
     * @param callback - function that performs the event handling
     */
    static void registerSFMLEvent(GameObjectPtr caller, std::function<void(GameObjectPtr&, sf::Event&)> callback);

    static void triggerSFMLEvents(sf::RenderWindow& window);
};


#endif //THE_STATION_EVENTMANAGER_H
