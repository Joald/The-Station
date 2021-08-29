#ifndef THE_STATION_EVENT_CONTAINER_H
#define THE_STATION_EVENT_CONTAINER_H

#include <map>
#include <memory>
#include <functional>
#include "Models/GameObject.h"


enum class GameEvent {
    EVENT_ZERO,

    SFML_EVENT,

    EVENT_LAST,
};

class EventContainer {
public:
    typedef std::shared_ptr<GameObject> GameObjectPtr;
    typedef std::function<void(GameObjectPtr&)> EventCallback;
    typedef std::map<GameObjectPtr, EventCallback> ObjectToCallbackMap;

    void registerEvent(GameObjectPtr& objectPtr, GameEvent event, EventCallback callback);
    void triggerEvent(GameEvent event);

private:

    std::map<GameEvent, ObjectToCallbackMap> events;
};


#endif //THE_STATION_EVENT_CONTAINER_H
