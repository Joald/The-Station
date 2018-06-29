#ifndef THE_STATION_GLOBALS_H
#define THE_STATION_GLOBALS_H


#include <string>

namespace Globals {

const std::string INSTALL = "INSTALL";
const std::string IMAGES = "IMAGES";
const std::string DATA = "DATA";
const std::string FOLDER_NAMES = "folder_names";

/**
 * Concatenates strings provided in the initializer list.
 * Faster than using std::string::operator+.
 * @return concatenation of strings in list
 */
std::string concat(std::initializer_list<std::string> list);

/**
 * Ignores all lines starting with '#' in a given file.
 * @param f
 */
void ignore_comments(std::ifstream& f);

/**
 * Scans the file passed as @fileName in the DATA directory.
 * If a line starts with @key, the rest of that line is returned,
 * skipping one leading character.
 * Throws an instance of std::logic_error if the value is not found.
 * @param fileName
 * @param key
 * @return
 */
std::string scanData(const std::string& fileName, const std::string& key);

/**
 * Returns the default extension of the given data type.
 * @return extension with a leading dot ('.')
 */
const std::string getExtension(const std::string& dataType);

/**
 * Returns the name of the folder associated with the given data type.
 * @return folder name with a trailing forward slash ('/')
 */
std::string getFolder(const std::string& dataType);

/**
 * Returns the absolute path to the folder associated with the given data type.
 * @param dataType
 * @return /absolute/path/to/folder/
 */
std::string absolutePath(const std::string& dataType);

/**
 * Returns a path to a resource called @resourceName of type @dataType with appropriate extension.
 * @param type
 * @param resourceName
 * @return /path/to/folder/then/resource.type
 */
std::string pathToResource(const std::string& type, const std::string& resourceName);

} // Globals


#endif //THE_STATION_GLOBALS_H
