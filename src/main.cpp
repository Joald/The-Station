#include "Models/Player.h"
#include "Events/EventManager.h"
#include "Time/Time.h"
#include "Rendering/CollisionDetector.h"
#include "Logging/Logger.h"

int main() {
    auto player = std::make_shared<Player>();
    auto& window = renderer();
    window.create(sf::VideoMode(800, 600), "TEST");
    debugAssert(window.isOpen(), "Could not open window.");
    window.add({player, 1});
    eventManager().registerSfmlEvent(
            "SFML_Closed_printing",
            sf::Event::Closed,
            [&](sf::Event) {
                logger(INFO) << "Closed!";
                window.close();
            }
    );
    eventManager().registerSfmlEvent(
            "Escape_to_Quit",
            sf::Event::KeyPressed,
            [&](sf::Event event) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
    );

    std::vector<CollisionGraph::Edge> edges = {
            std::make_pair(player->getID(), "screenEdge"),
    };

    auto graph = std::make_shared<CollisionGraph>(std::move(edges));

    STEngine::registerCollisionDetector(
            std::make_shared<STEngine::CollisionDetector>(std::move(graph))
    );

    player->setPosition(200, 200);
    while (window.isOpen()) {
        Time::update();
        eventManager().triggerSfmlEvents(window);
        window.render();
    }

}