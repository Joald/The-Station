#include <fstream>
#include <filesystem>
#include <unordered_map>

#include "Filesystem/Filesystem.h"
#include "Globals/Globals.h"

namespace fs = std::filesystem;

using Globals::FolderName;

namespace STEngine::Filesystem {

namespace {

const std::string_view fileNames[] = {
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
    std::unordered_map<std::string_view, DataMap> map;
    for (auto fileName : fileNames) {
        auto path = (basePath() / "data" / fileName).replace_extension(".txt");
        std::ifstream file(path);
        if (!file) {
            throw std::logic_error("Installation corrupted. Could not read file at " + path.string());
        }
        ignore_comments(file);

        auto& submap = map[fileName];
        scanFile(submap, file);
    }
    return map;
}

} // namespace


fs::path basePath() {
    return "..";
}

std::string_view scanData(std::string_view fileName, std::string_view key) {
    static auto map = initVars();
    try {
        const auto& submap = map.at(fileName);
        try {
            return submap.at(std::string(key));
        } catch (std::out_of_range&) {
            std::stringstream s;
            s << "Variable \"" << key << "\" not found in file \"" << fileName << "\".";
            throw std::logic_error(s.str());
        }
    } catch (std::out_of_range&) {
        std::stringstream s;
        s << "Data file \"" << fileName << "\" not found.";
        throw std::logic_error(s.str());
    }
}

std::string_view getFolder(std::string_view dataType) {
    return scanData(Globals::resolveFolderName(FolderName::FolderNames), dataType);
}

fs::path pathToResource(std::string_view type, std::string_view resourceName) {
    return (absolutePath(type) / resourceName).replace_extension(getExtension(type));
}

fs::path absolutePath(std::string_view dataType) {
    return basePath() / getFolder(dataType);
}

std::string_view getExtension(std::string_view dataType) {
    return scanData(Globals::resolveFolderName(FolderName::Extensions), dataType);
}


void ignore_comments(std::ifstream &f) {
    while (f.peek() == '#') {
        f.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

} // STEngine::Filesystem