#ifndef THE_STATION_GLOBALS_H
#define THE_STATION_GLOBALS_H


#include <string>

namespace Globals {

const std::string INSTALL = "INSTALL";
const std::string IMAGES = "IMAGES";
const std::string DATA = "DATA";
const std::string SHADERS = "SHADERS";
const std::string FOLDER_NAMES = "folder_names";

/**
 * Concatenates strings provided in the initializer list.
 * Faster than using std::string::operator+.
 * @return concatenation of strings in list
 */
std::string concat(std::initializer_list<std::string> list);

} // Globals


#endif //THE_STATION_GLOBALS_H
