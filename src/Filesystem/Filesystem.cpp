#include <fstream>
#include "Filesystem/Filesystem.h"
#include "Globals/Globals.h"

namespace STEngine::Filesystem {

std::string scanData(const std::string &fileName, const std::string &key) {
    std::ifstream f(Globals::concat({"../data/", fileName, ".txt"}));
    ignore_comments(f);
    if (!f) {
        throw std::logic_error("Installation corrupted.");
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

std::string pathToResource(const std::string &type, const std::string &resourceName) {
    return Globals::concat({absolutePath(type), resourceName, getExtension(type)});
}

std::string absolutePath(const std::string &dataType) {
    return Globals::concat({getFolder(Globals::INSTALL), getFolder(dataType)});
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