#include "EventContainer.h"

void EventContainer::registerEvent(GameObjectPtr& objectPtr, GameEvent event, EventCallback callback) {
    events[event].emplace(objectPtr, callback);
}

void EventContainer::triggerEvent(GameEvent event) {
    for (auto& i : events[event]) {
        i.second(const_cast<GameObjectPtr&>(i.first));
    }
}
