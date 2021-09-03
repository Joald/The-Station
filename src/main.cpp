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
    collisionDetectors().emplace(
      player->getName(),
      std::make_shared<CollisionGraph>(
        std::vector<CollisionGraph::Edge>(1, std::make_pair(std::string(player->getName()), "screenEdge"))
      )
    );

    player->setPosition(200, 200);
    while (window.isOpen()) {
        Time::update();
        EventManager::triggerSfmlEvents(window);
        window.render();
    }

}