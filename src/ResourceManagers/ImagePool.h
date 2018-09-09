#ifndef THE_STATION_IMAGE_POOL_H
#define THE_STATION_IMAGE_POOL_H


#include <SFML/Graphics.hpp>
#include "ResourcePool.h"

class ImagePool : public ResourcePool<sf::Image> {
    storage_t::iterator loadResource(const std::string& id) override;
};

ImagePool& imagePool();

#endif //THE_STATION_IMAGE_POOL_H
