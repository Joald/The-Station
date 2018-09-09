#ifndef THE_STATION_TEXTURE_POOL_H
#define THE_STATION_TEXTURE_POOL_H


#include <SFML/Graphics/Texture.hpp>
#include "ResourcePool.h"

class TexturePool : public ResourcePool<sf::Texture> {
    storage_t::iterator loadResource(const std::string& id) override;
};

TexturePool& texturePool();

#endif //THE_STATION_TEXTURE_POOL_H
