#include "EventContainer.h"

void EventContainer::registerEvent(GameObjectPtr& objectPtr, GameEvent event, EventCallback callback) {
    events[event].emplace(objectPtr, callback);
}

void EventContainer::triggerEvent(GameEvent event) {
    for (auto&[object, callback] : events[event]) {
        callback(const_cast<GameObjectPtr&>(object));
    }
}
