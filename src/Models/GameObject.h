#ifndef THE_STATION_GAME_OBJECT_H
#define THE_STATION_GAME_OBJECT_H

#include <string>
#include <unordered_set>

/**
 * Base class for anything represented in any way in the game's logic.
 */
class GameObject {
    inline static std::unordered_set<std::string> ids;
    std::string ID;
protected:
    explicit GameObject(std::string id = "");
public:
    virtual ~GameObject() = default;

    std::string_view getID() { return ID; }
};


#endif //THE_STATION_GAME_OBJECT_H
