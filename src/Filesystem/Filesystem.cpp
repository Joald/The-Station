#include <fstream>
#include <filesystem>

#include "Filesystem/Filesystem.h"
#include "Globals/Globals.h"

namespace fs = std::filesystem;

namespace STEngine::Filesystem {

fs::path basePath() {
    return "..";
}

std::string scanData(const std::string &fileName, const std::string &key) {
    auto path = (basePath() / "data" / fileName).replace_extension(".txt");
    std::ifstream f(path);
    ignore_comments(f);
    if (!f) {
        throw std::logic_error("Installation corrupted. Could not read file at " + path.string());
    }
    std::string s;
    while (getline(f, s)) {
        if (s.substr(0, key.size()) == key) {
            // if there is nothing but the key return empty string
            return s.size() == key.size() ? "" : s.substr(key.size() + 1);
        }
    }
    throw std::logic_error("Requested installation-specific variable not found.");
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