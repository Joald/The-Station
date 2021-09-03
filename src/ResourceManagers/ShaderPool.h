#ifndef THE_STATION_IMAGE_POOL_H
#define THE_STATION_IMAGE_POOL_H


#include <SFML/Graphics.hpp>
#include "ResourcePool.h"

class ShaderPool : public ResourcePool<sf::Shader> {
    storage_t::iterator loadResource(std::string_view id) override;
};

ShaderPool& shaderPool();

#endif //THE_STATION_IMAGE_POOL_H
