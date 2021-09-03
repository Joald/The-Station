#ifndef THE_STATION_GLOBALS_H
#define THE_STATION_GLOBALS_H


#include <string>
#include <Logging/Logger.h>

enum class FolderName {
    Install,
    Images,
    Data,
    Shaders,
    FolderNames,
    Extensions,
};

constexpr std::string_view resolveFolderName(FolderName name) {
    switch (name) {
        case FolderName::Install:
            return "INSTALL";
        case FolderName::Images:
            return "IMAGES";
        case FolderName::Data:
            return "DATA";
        case FolderName::Shaders:
            return "SHADERS";
        case FolderName::FolderNames:
            return "folder_names";
        case FolderName::Extensions:
            return "extensions";
    }
    debugLog("Impossible path taken. Exiting...");
    std::exit(1);
}

namespace Globals {

/**
 * Concatenates strings provided in the initializer list.
 * Faster than using std::string::operator+.
 * @return concatenation of strings in list
 */
std::string concat(std::initializer_list<std::string> list);

} // Globals


#endif //THE_STATION_GLOBALS_H
