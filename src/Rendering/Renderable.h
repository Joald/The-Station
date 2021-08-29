#ifndef THE_STATION_RENDERABLE_H
#define THE_STATION_RENDERABLE_H


#include <SFML/Graphics.hpp>
#include "ResourceManagers/TexturePool.h"
#include "ResourceManagers/ShaderPool.h"
#include "CollisionShape.h"


/**
 * Polymorphic base for all Renderables.
 */
class RenderableBase : public sf::Sprite {
public:
    virtual const char* getName() const = 0;

    virtual sf::Shader* getShader() const = 0;
};

/**
 * Base class for anything that can be displayed on the screen.
 * @tparam name - name of the texture
 * @tparam hasShader - if a shader with name @name should be loaded and displayed.
 */
template<const char* name, bool hasShader = false>
class Renderable : public virtual RenderableBase {
    std::shared_ptr <sf::Shader> shader;
protected:
    ResourcePool<sf::Texture>::ptr texture;

    explicit Renderable() :
      shader(),
      texture(texturePool().getResourceById(name)) {
        setTexture(*texture);
        if (hasShader) {
            shader = shaderPool().getResourceById(name);
        }
    }

public:
    const char* getName() const override {
        return name;
    }

    sf::Shader* getShader() const override {
        return hasShader ? shader.get() : nullptr;
    }
};


#endif //THE_STATION_RENDERABLE_H
