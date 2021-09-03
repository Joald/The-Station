#ifndef THE_STATION_RENDERABLE_H
#define THE_STATION_RENDERABLE_H


#include <SFML/Graphics.hpp>
#include "ResourceManagers/TexturePool.h"
#include "ResourceManagers/ShaderPool.h"
#include "CollisionShape.h"


/**
 * Base class for anything that can be displayed on the screen.
 * @tparam name - name of the texture
 * @tparam hasShader - if a shader with name @name should be loaded and displayed.
 */
class Renderable : public sf::Sprite {
    std::string_view name;
    std::shared_ptr<sf::Shader> shader;
protected:
    ResourcePool<sf::Texture>::ptr texture;

    explicit Renderable(std::string_view name, bool loadShader = false) :
            name(name),
            shader(loadShader ? shaderPool().getResourceById(name) : nullptr),
            texture(texturePool().getResourceById(name)) {
        setTexture(*texture);
    }

public:
    [[nodiscard]] std::string_view getName() const {
        return name;
    }

    [[nodiscard]] sf::Shader& getShader() {
        return *shader;
    }
};


#endif //THE_STATION_RENDERABLE_H
