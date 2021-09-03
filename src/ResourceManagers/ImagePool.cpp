#include <fstream>
#include <Filesystem/Filesystem.h>
#include "ImagePool.h"
#include "Exceptions/ResourceNotFoundError.h"
#include "Globals/Globals.h"


ImagePool::storage_t::iterator ImagePool::loadResource(std::string_view id) {
    using namespace Globals;

    auto it = storage.emplace(id, std::make_shared<sf::Image>()).first;
    auto filePath = STEngine::Filesystem::pathToResource(resolveFolderName(FolderName::Images), id);
    if (!it->second->loadFromFile(filePath)) {
        throw ResourceNotFoundError(concat({"Image ", filePath, " could not be loaded."}));
    }
    return it;
}

ImagePool& imagePool() {
    static ImagePool pool;
    return pool;
}
