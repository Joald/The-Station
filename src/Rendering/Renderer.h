#ifndef THE_STATION_RENDERER_H
#define THE_STATION_RENDERER_H


#include <SFML/Graphics.hpp>
#include <memory>
#include <set>
#include "Models/GameObject.h"
#include "ResourceManagers/ResourcePool.h"
#include "ResourceManagers/TexturePool.h"
#include "Logging/Logger.h"
#include "ResourceManagers/ShaderPool.h"
#include "Renderable.h"

class Renderer : public GameObject, public sf::RenderWindow {
    using RenderablePointer = std::pair<std::shared_ptr<Renderable>, int>;

    struct RenderableComparator {
        bool operator()(const RenderablePointer& lhs, const RenderablePointer& rhs) const {
            return lhs.second < rhs.second;
        }
    };

    std::set<RenderablePointer, RenderableComparator> renderables;
public:
    void add(RenderablePointer renderablePointer) {
        auto [iterator, success] = renderables.emplace(std::move(renderablePointer));
        if (success) {
            debugLog("Added renderable \"", iterator->first->getTextureName(), "\"!");
        }
    }

    void remove(const RenderablePointer& renderablePointer) {
        renderables.erase(renderablePointer);
    }

    void render() {
        clear(sf::Color::White);
        for (auto&[renderable, priority] : renderables) {
            draw(*renderable, &renderable->getShader());
        }
        display();
    }
};


Renderer& renderer();


#endif //THE_STATION_RENDERER_H
