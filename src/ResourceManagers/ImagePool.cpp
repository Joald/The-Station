#include <fstream>
#include "ImagePool.h"
#include "../Exceptions/ResourceNotFoundError.h"
#include "../Globals.h"

namespace {
} // namespace


ImagePool::storage_t::iterator ImagePool::loadResource(const std::string& id) {
    using namespace Globals;

    auto it = imageStorage.emplace(id, std::make_shared<sf::Image>()).first;
    auto filePath = pathToResource(IMAGES, id);
    if (!it->second->loadFromFile(filePath)) {
        throw ResourceNotFoundError(concat({"Image ", filePath, " could not be loaded."}));
    }
    return it;
}

ImagePool::ptr ImagePool::getResourceById(const std::string& id) {
    auto iter = imageStorage.find(id);
    if (iter == imageStorage.end()) {
        iter = loadResource(id);
    }
    return iter->second;
}
/*
void ImagePool::initialize() {
    using namespace Globals;
    std::ifstream f(pathToResource(DATA, "images"));
    ignore_comments(f);
    std::string s;
    while (std::getline(f, s)) {

    }
    for (int i = 0; i < images.size(); ++i) {
        idStorage.push_back(static_cast<ImageID>(i));
    }
    for (auto& id : idStorage) {
        std::string filePath = pathToResource(IMAGES, images[static_cast<int>(id)]);
        auto it = imageStorage.emplace(id, sf::Image()).first;
        if (!it->second.loadFromFile(filePath)) {
            throw ResourceNotFoundError(concat({"Image ", filePath, " could not be loaded."}));
        }
    }
}
*/
