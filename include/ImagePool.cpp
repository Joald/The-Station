//
// Created by joald on 04.11.17.
//

#include "ImagePool.h"

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
} // namespace

sf::Image &ImagePool::getImageById(ImageID id) {
    auto iter = idStorage.find(id);
    if (iter == idStorage.end()) {
        throw ResourceNotFoundError("Image not found.");
    }
    return iter->second;
}

sf::Image &&ImagePool::loadImage(const std::string &name) {
    sf::Image image;
    if (!image.loadFromFile(DEFAULT_IMAGE_FOLDER_PATH + name)) {
        throw ResourceNotFoundError("Image " + name + " could not be loaded.");
    }
    return std::move(image);
}

void ImagePool::initialize() {
    for (int i = PLAYER; i != LAST; ++i) {
        idStorage.emplace({i, loadImage(images[i])});
    }
}
