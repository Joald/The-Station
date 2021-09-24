#ifndef THE_STATION_GLOBALS_H
#define THE_STATION_GLOBALS_H


#include <string>
#include <Logging/Logger.h>

namespace Globals {

enum class FolderName {
    Install,
    Images,
    Data,
    Shaders,
    FolderNames,
    Extensions,
};

constexpr std::string_view resolveFolderName(FolderName name){
    using enum FolderName;
    switch (name) {
        case Install:
            return "INSTALL";
        case Images:
            return "IMAGES";
        case Data:
            return "DATA";
        case Shaders:
            return "SHADERS";
        case FolderNames:
            return "folder_names";
        case Extensions:
            return "extensions";
    }
    logger(FATAL) << "Impossible path taken. Exiting...";
    std::exit(1);
}

/**
 * Concatenates strings provided in the initializer list.
 * Faster than using std::string::operator+.
 * @return concatenation of strings in list
 */
std::string concat(std::initializer_list<std::string> list);

} // Globals


#endif //THE_STATION_GLOBALS_H
