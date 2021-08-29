#include <fstream>
#include <Filesystem/Filesystem.h>
#include "ImagePool.h"
#include "Exceptions/ResourceNotFoundError.h"
#include "Globals/Globals.h"


ImagePool::storage_t::iterator ImagePool::loadResource(const std::string& id) {
    using namespace Globals;

    auto it = storage.emplace(id, std::make_shared<sf::Image>()).first;
    auto filePath = STEngine::Filesystem::pathToResource(IMAGES, id);
    if (!it->second->loadFromFile(filePath)) {
        throw ResourceNotFoundError(concat({"Image ", filePath, " could not be loaded."}));
    }
    return it;
}

ImagePool& imagePool() {
    static ImagePool pool;
    return pool;
}
