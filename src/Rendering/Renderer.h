#ifndef THE_STATION_RENDERER_H
#define THE_STATION_RENDERER_H


#include <SFML/Graphics.hpp>
#include <memory>
#include <set>
#include "../Models/GameObject.h"
#include "../ResourceManagers/ResourcePool.h"
#include "../ResourceManagers/TexturePool.h"
#include "../Logging/Logger.h"

class RenderableBase : public sf::Sprite {
public:
    virtual const char* getName() = 0;
};

template<const char* c>
class Renderable : public RenderableBase {
protected:
    ResourcePool<sf::Texture>::ptr texture;

    Renderable() : texture(texturePool().getResourceById(c)) {
        setTexture(*texture);
    }

public:
    const char* getName() override {
        return c;
    }
};

class Renderer : public GameObject, public sf::RenderWindow {
    using RenderablePointer = std::shared_ptr<RenderableBase>;
    std::set<RenderablePointer> renderables;
public:
    void add(RenderablePointer renderablePointer) {
        auto [iterator, success] = renderables.insert(std::move(renderablePointer));
        if (success) {
            debugLog("Added renderable \"", (*iterator)->getName(), "\"!");
        }
    }

    void remove(const RenderablePointer& renderablePointer) {
        renderables.erase(renderablePointer);
    }

    void render() {
        clear(sf::Color::White);
        for (auto& renderable : renderables) {
            draw(*renderable);
        }
        display();
    }
};


Renderer& renderer();


#endif //THE_STATION_RENDERER_H
