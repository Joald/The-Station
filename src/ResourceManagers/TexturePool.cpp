#include "TexturePool.h"
#include "Logging/Logger.h"
#include "ImagePool.h"


TexturePool::storage_t::iterator TexturePool::loadResource(std::string_view id) {
    auto[iterator, inserted] = storage.insert({id, std::make_shared<sf::Texture>()});
    if (inserted) {
        iterator->second->loadFromImage(*imagePool().getResourceById(id));
        logger() << "New texture " << id << " loaded from image!";
    } else {
        logger() << "Texture " << id << " already here!";
    }
    return iterator;
}

TexturePool& texturePool() {
    static TexturePool pool;
    return pool;
}
