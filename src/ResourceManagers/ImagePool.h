#ifndef THE_STATION_IMAGE_POOL_H
#define THE_STATION_IMAGE_POOL_H


#include <SFML/Graphics.hpp>
#include "ResourcePool.h"

class ImagePool : ResourcePool<sf::Image> {
    storage_t imageStorage;
    storage_t::iterator loadResource(const std::string& id) override;

public:
    ptr getResourceById(const std::string& id);
};


#endif //THE_STATION_IMAGE_POOL_H
