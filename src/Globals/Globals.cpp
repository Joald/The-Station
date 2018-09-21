#include <fstream>
#include "Globals.h"

namespace {

} // namespace


std::string Globals::concat(std::initializer_list<std::string> list) {
    std::string s;
    for (auto& i : list) {
        s += i;
    }
    return s;
}

std::string Globals::scanData(const std::string& fileName, const std::string& key) {
    std::ifstream f(concat({"../data/", fileName, ".txt"}));
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

std::string Globals::getFolder(const std::string& dataType) {
    return scanData(FOLDER_NAMES, dataType);
}

std::string Globals::pathToResource(const std::string& type, const std::string& resourceName) {
    return concat({absolutePath(type), resourceName, getExtension(type)});
}

std::string Globals::absolutePath(const std::string& dataType) {
    return concat({getFolder(INSTALL), getFolder(dataType)});
}

const std::string Globals::getExtension(const std::string& dataType) {
    return scanData("extensions", dataType);
}

void Globals::ignore_comments(std::ifstream& f) {
    while (f.peek() == '#') {
        f.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}
