#include "Models/Player.h"
#include "Events/EventManager.h"
#include "Time/Time.h"
#include "Rendering/CollisionDetector.h"

int main() {
    auto player = std::make_shared<Player>();
    auto& window = renderer();
    window.create(sf::VideoMode(800, 600), "TEST");
    debugAssert(window.isOpen(), "Could not open window.");
    window.add({player, 1});
    EventManager::registerSfmlEvent(
            sf::Event::Closed, [&](sf::Event event) {
                debugLog("Closed!");
                window.close();
            }
    );
    EventManager::registerSfmlEvent(
            sf::Event::KeyPressed, [&](sf::Event event) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
    );

    std::vector<CollisionGraph::Edge> edges = {
            std::make_pair(std::string(player->getName()), "screenEdge"),
    };

    auto graph = std::make_shared<CollisionGraph>(std::move(edges));

    STEngine::collisionDetectors().emplace(
            player->getName(),
            std::move(graph)
    );

    player->setPosition(200, 200);
    while (window.isOpen()) {
        Time::update();
        EventManager::triggerSfmlEvents(window);
        window.render();
    }

}