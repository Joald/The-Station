//
// Created by joald on 04.11.17.
//

#include "ImagePool.h"

std::unordered_map<ImageID, sf::Image> ImagePool::imageStorage;
std::vector<ImageID> ImagePool::idStorage;
const std::string ImagePool::DEFAULT_IMAGE_FOLDER_PATH = "/home/joald/The-Station/img/"; //


namespace {
    const std::vector<std::string> images = {
            "playerTexture.png",
            "bg.png",
            "subliminal.png",
            "gui.png",
            "explosion.png",
            "items.png",
            "bossroom.png",
            "boss.png",
            "loading.png",
            "timing.png",
            "invent.png",
            "select.png",
            "doorup.png",
            "doorbot.png",
            "doorleft.png",
            "doorright.png",
            "newgame.png",
            "title.png",
            "exitTexture.png",
            "options.png",
            "pause.png",
            "optionsButtonPauseMenuTexture.png",
            "pauseExitTexture.png",
            "pauseMenuTexture.png",
            "endscreen.png",
            "optionsMenuBackgroundTexture.png",
            "weapon.png",
            "floor_tile.png"
    };// should be kept in the same order as ImageID enums defined in ../include/ImagePool.h
    ///TODO rework so that list is in a file
} // namespace

sf::Image &ImagePool::getImageById(ImageID id) {
    auto iter = imageStorage.find(id);
    auto id_int = static_cast<int>(id);
    if (iter == imageStorage.end()) {
        throw ResourceNotFoundError("Image " + DEFAULT_IMAGE_FOLDER_PATH + images[id_int] + " not found.");
    }
    return iter->second;
}

void ImagePool::initialize() {
    for (int i = 0; i < images.size(); ++i) {
        idStorage.push_back(static_cast<ImageID>(i));
    }
    for (auto& id : idStorage) {
        auto id_int = static_cast<int>(id);
        const std::string &name = images[id_int];
        imageStorage.emplace(id, sf::Image());
        if (!imageStorage.at(id).loadFromFile(DEFAULT_IMAGE_FOLDER_PATH + name)) {
            throw ResourceNotFoundError("Image " + DEFAULT_IMAGE_FOLDER_PATH + name + " could not be loaded.");
        }
    }
}
