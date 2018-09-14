#include <cassert>
#include "Models/Player.h"
#include "Events/EventManager.h"

int main() {
    auto player = std::make_shared<Player>();
    auto& window = renderer();
    window.create(sf::VideoMode(800, 600), "TEST");
    assert(window.isOpen());
    window.add({player, 1});
    EventManager::registerSFMLEvent(nullptr,
      [&] (std::shared_ptr<GameObject> renderer, sf::Event event) {
        if (event.type == sf::Event::Closed) {
            debugLog("Closed!");
            window.close();
        }
    });
    player->setPosition(200, 200);

    while (window.isOpen()) {
        EventManager::triggerSFMLEvents(window);
        window.render();
    }

}