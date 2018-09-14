#ifndef THE_STATION_RENDERER_H
#define THE_STATION_RENDERER_H


#include <SFML/Graphics.hpp>
#include <memory>
#include <set>
#include "../Models/GameObject.h"
#include "../ResourceManagers/ResourcePool.h"
#include "../ResourceManagers/TexturePool.h"
#include "../Logging/Logger.h"
#include "../ResourceManagers/ShaderPool.h"

class RenderableBase : public sf::Sprite {
public:
    virtual const char* getName() const = 0;
    virtual sf::Shader* getShader() const = 0;
};


template<const char* name, bool hasShader>
class Renderable : public RenderableBase {
    std::shared_ptr<sf::Shader> shader;
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

class Renderer : public GameObject, public sf::RenderWindow {
    using RenderablePointer = std::pair<std::shared_ptr<RenderableBase>, int>;

    struct RenderableComparator {
        bool operator()(const RenderablePointer& lhs, const RenderablePointer& rhs) const {
            return lhs.second < rhs.second;
        }
    };

    std::set<RenderablePointer, RenderableComparator> renderables;
public:
    void add(RenderablePointer renderablePointer) {
        auto [iterator, success] = renderables.insert(std::move(renderablePointer));
        if (success) {
            debugLog("Added renderable \"", (*iterator).first->getName(), "\"!");
        }
    }

    void remove(const RenderablePointer& renderablePointer) {
        renderables.erase(renderablePointer);
    }

    void render() {
        clear(sf::Color::White);
        for (auto&[renderable, priority] : renderables) {
            draw(*renderable, renderable->getShader());
        }
        display();
    }
};


Renderer& renderer();


#endif //THE_STATION_RENDERER_H
