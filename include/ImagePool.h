//
// Created by joald on 04.11.17.
//

#ifndef THE_STATION_IMAGE_POOL_H
#define THE_STATION_IMAGE_POOL_H


#include "The_Station.h"

enum class ImageID {
    PLAYER,
    BACKGROUND,
    SUBLIMINAL,
    GUI,
    EXPLOSION,
    ITEMS,
    BOSSROOM,
    BOSS,
    LOADING,
    TIMING,
    INVENT,
    SELECT,
    DOORUP,
    DOORBOT,
    DOORLEFT,
    DOORRIGHT,
    NEWGAME,
    TITLE,
    EXIT,
    OPTIONS,
    PAUSE,
    OPTIONP,
    EXITP,
    MENUP,
    ENDSCREEN,
    OPTIONSMAIN,
    WEAPON,
    FLOOR_TILE_TEXTURE,
    ENEMY,
    LAST
}; // modify together with the string vector images in ImagePool.cpp

class ImagePool : public ResourcePool{
    static std::unordered_map<ImageID, sf::Image> imageStorage;
    static std::vector<ImageID> idStorage;
public:
    static const std::string DEFAULT_IMAGE_FOLDER_PATH;

    static void initialize();
    static sf::Image& getImageById(ImageID id);
};


#endif //THE_STATION_IMAGE_POOL_H
