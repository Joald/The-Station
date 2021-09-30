#include "Renderer.h"
#include "Logging/Logger.h"

Renderer& renderer() {
    static Renderer render;
    return render;
}

void Renderer::add(Renderer::RenderablePointer renderablePointer) {
    auto[iterator, success] = renderables.emplace(std::move(renderablePointer));
    if (success) {
        logger(INFO) << "Added renderable \"" << iterator->first->getTextureName() << "\"!";
    }
}

void Renderer::render() {
    clear(sf::Color::White);
    for (const auto&[renderable, priority] : renderables) {
        draw(*renderable, &renderable->getShader());
    }
    display();
}
