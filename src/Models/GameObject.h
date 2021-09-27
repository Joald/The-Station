#ifndef THE_STATION_GAME_OBJECT_H
#define THE_STATION_GAME_OBJECT_H

#include <string>
#include <unordered_set>
#include <map>

/**
 * Base class for anything represented in any way in the game's logic.
 */
class GameObject {
    inline static std::unordered_set<std::string> ids;
    std::string ID;
    std::map<std::string_view, std::string> idCache;
protected:
    explicit GameObject(std::string id = "");
public:
    virtual ~GameObject() = default;

    std::string_view getID() { return ID; }

    std::string_view generateID(std::string_view key);
};


#endif //THE_STATION_GAME_OBJECT_H
