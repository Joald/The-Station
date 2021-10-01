#ifndef THE_STATION_GAME_OBJECT_H
#define THE_STATION_GAME_OBJECT_H

#include <string>
#include <unordered_set>
#include <map>

/**
 * Base class for anything represented in any way in the game's logic.
 */
class GameObject {
    std::string ID;
    std::map<std::string_view, std::string> idCache;
protected:
    explicit GameObject(std::string id = "");
public:
    virtual ~GameObject() noexcept = default;
    GameObject(GameObject&&) = delete;
    GameObject(const GameObject&) = delete;
    GameObject& operator=(GameObject&&) = delete;
    GameObject& operator=(const GameObject&) = delete;

    std::string_view getID() { return ID; }

    std::string_view generateID(std::string_view key);
};


#endif //THE_STATION_GAME_OBJECT_H
