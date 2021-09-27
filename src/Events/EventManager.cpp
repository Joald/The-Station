#include <SFML/Graphics/RenderWindow.hpp>
#include <variant>
#include "EventManager.h"
#include "Rendering/Renderer.h"

struct EventBase;
//struct KeyHoldEvent;

class EventManagerImpl : public EventManager {
//    using Event = std::variant<SFMLEvent, KeyHoldEvent>;
    // TODO: custom allocator for this
    using EventSet = std::set<std::shared_ptr<EventBase>>;
    EventSet events;
    using IteratorVector = std::vector<EventSet::iterator>;
    std::map<sf::Event::EventType, IteratorVector> eventsBySFMLType;
    std::map<sf::Keyboard::Key, IteratorVector> eventsByKeyHeld;
    std::map<std::string_view, EventSet::iterator> eventsByID;
public:
    ~EventManagerImpl() noexcept = default;

    void registerSfmlEvent(std::string_view id, sf::Event::EventType eventType,
                           std::function<void(sf::Event)> callback) override;

    void triggerSfmlEvents(sf::RenderWindow& window) override;

    void registerKeyHold(std::string_view id, sf::Keyboard::Key key,
                         std::function<void()> callback) override;

    void unregisterEvent(std::string_view id) override;

    void changeEvent(std::string_view id, std::any callback) override;
};

struct EventBase {
    enum struct EventType {
        SFML_EVENT,
        KEY_HOLD_EVENT,
    };
    EventType eventType;
};

struct SFMLEvent : public EventBase {
    SFMLEvent(std::string_view id,
              std::function<void(sf::Event)> callback,
              sf::Event::EventType sfmlEventType) :
            EventBase({EventType::SFML_EVENT}), id(id),
            callback(std::move(callback)),
            sfmlEventType(sfmlEventType) {}

    std::string_view id;
    std::function<void(sf::Event)> callback;
    sf::Event::EventType sfmlEventType;
};

struct KeyHoldEvent : public EventBase {
    KeyHoldEvent(std::string_view id,
                 std::function<void()> callback,
                 sf::Keyboard::Key key) :
            EventBase({EventType::KEY_HOLD_EVENT}), id(id),
            callback(std::move(callback)),
            key(key) {}

    std::string_view id;
    std::function<void()> callback;
    sf::Keyboard::Key key;
};


void EventManagerImpl::registerSfmlEvent(std::string_view id, sf::Event::EventType eventType,
                                         std::function<void(sf::Event)> callback) {
    auto[it, inserted] = events.emplace(
            std::make_shared<SFMLEvent>(id, std::move(callback), eventType));
    eventsByID[id] = it;
    eventsBySFMLType[eventType].emplace_back(it);
}


void EventManagerImpl::registerKeyHold(std::string_view id, sf::Keyboard::Key key,
                                       std::function<void()> callback) {
    auto[it, inserted] = events.emplace(std::make_shared<KeyHoldEvent>(id, std::move(callback), key));
    eventsByID[id] = it;
    eventsByKeyHeld[key].emplace_back(it);
}

void EventManagerImpl::unregisterEvent(std::string_view id) {
    auto it = eventsByID.at(id);

    // remove from ID map
    eventsByID.erase(id);
    auto& event = *it;

    // remove from event-type-specific map
    auto& eventVector = [&] () -> IteratorVector& {
        switch (event->eventType) {
            case EventBase::EventType::SFML_EVENT: {
                auto sfmlEvent = std::static_pointer_cast<SFMLEvent>(event);
                return eventsBySFMLType.at(sfmlEvent->sfmlEventType);
            }
            case EventBase::EventType::KEY_HOLD_EVENT: {
                auto keyHoldEvent = std::static_pointer_cast<KeyHoldEvent>(event);
                return eventsByKeyHeld.at(keyHoldEvent->key);
            }
        }
        logger(FATAL) << "Insufficient switch cases. Exiting...";
        std::exit(1);
    }();
    eventVector.erase(std::ranges::find(eventVector, it));

    // remove from event storage
    events.erase(it);
}

void EventManagerImpl::triggerSfmlEvents(sf::RenderWindow& window) {
    sf::Event sfmlEvent{};
    while (window.pollEvent(sfmlEvent)) {
        auto it = eventsBySFMLType.find(sfmlEvent.type);
        if (it != eventsBySFMLType.end()) {
            for (const auto& registration: it->second) {
                std::static_pointer_cast<SFMLEvent>(*registration)->callback(sfmlEvent);
            }
        }
    }
    for (auto&[key, registrations]: eventsByKeyHeld) {
        if (sf::Keyboard::isKeyPressed(key)) {
            for (auto& registration: registrations) {
                std::static_pointer_cast<KeyHoldEvent>(*registration)->callback();
            }
        }
    }
}

void EventManagerImpl::changeEvent(std::string_view id, std::any callback) {
    auto it = eventsByID.find(id);
    if (it != eventsByID.end()) {
        auto& ptr = *it->second;
        switch (ptr->eventType) {
            case EventBase::EventType::SFML_EVENT: {
                auto cast_ptr = std::static_pointer_cast<SFMLEvent>(ptr);
                cast_ptr->callback = std::any_cast<decltype(cast_ptr->callback)>(callback);
                break;
            }
            case EventBase::EventType::KEY_HOLD_EVENT: {
                auto cast_ptr = std::static_pointer_cast<KeyHoldEvent>(ptr);
                cast_ptr->callback = std::any_cast<decltype(cast_ptr->callback)>(callback);
                break;
            }
        }
    }
}

EventManager& eventManager() {
    static auto manager = EventManagerImpl{};
    return manager;
}
