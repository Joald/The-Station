#include <fstream>
#include <filesystem>
#include <unordered_map>

#include "Filesystem/Filesystem.h"
#include "Globals/Globals.h"

namespace fs = std::filesystem;

namespace STEngine::Filesystem {

namespace {

const std::string fileNames[] = {
        "extensions",
        "folder_names",
        "id_list",
        "images",
};

using DataMap = std::unordered_map<std::string, std::string>;

void scanFile(DataMap& map, std::ifstream& file) {
    std::string line;
    while (getline(file, line)) {
        auto spacePos = line.find(' ');

        map[line.substr(0, spacePos)] = spacePos == std::string::npos ? "" : line.substr(spacePos + 1);
    }
}

auto initVars() {
    std::unordered_map<std::string, DataMap> map;
    for (auto fileName : fileNames) {
        auto path = (basePath() / "data" / fileName).replace_extension(".txt");
        std::ifstream file(path);
        if (!file) {
            throw std::logic_error("Installation corrupted. Could not read file at " + path.string());
        }
        ignore_comments(file);

        auto& submap = map[std::move(fileName)];
        scanFile(submap, file);
    }
    return map;
}

} // namespace


fs::path basePath() {
    return "..";
}

std::string scanData(const std::string &fileName, const std::string &key) {
    static auto map = initVars();
    try {
        const auto& submap = map.at(fileName);
        try {
            return submap.at(key);
        } catch (std::out_of_range&) {
            throw std::logic_error("Variable \"" + key + "\" not found in file \"" + fileName + "\".");
        }
    } catch (std::out_of_range&) {
        throw std::logic_error("Data file \"" + fileName + "\" not found.");
    }
}

std::string getFolder(const std::string &dataType) {
    return scanData(Globals::FOLDER_NAMES, dataType);
}

fs::path pathToResource(const std::string &type, const std::string &resourceName) {
    return (absolutePath(type) / resourceName).replace_extension(getExtension(type));
}

fs::path absolutePath(const std::string &dataType) {
    return basePath() / getFolder(dataType);
}

std::string getExtension(const std::string &dataType) {
    return scanData("extensions", dataType);
}


void ignore_comments(std::ifstream &f) {
    while (f.peek() == '#') {
        f.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

} // STEngine::Filesystem