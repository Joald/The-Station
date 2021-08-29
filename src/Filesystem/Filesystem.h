#ifndef THE_STATION_FILESYSTEM_H
#define THE_STATION_FILESYSTEM_H

#include <string>
#include <filesystem>

namespace STEngine::Filesystem {

std::filesystem::path basePath();

/**
* Scans the file passed as @fileName in the DATA directory.
* If a line starts with @key, the rest of that line is returned,
* skipping one leading character.
* Throws an instance of std::logic_error if the value is not found.
* @param fileName
* @param key
* @return
*/
std::string scanData(const std::string &fileName, const std::string &key);

/**
* Returns the default extension of the given data type.
* @return extension with a leading dot ('.')
*/
std::string getExtension(const std::string &dataType);

/**
* Returns the name of the folder associated with the given data type.
* @return folder name
*/
std::string getFolder(const std::string &dataType);

/**
* Returns the absolute path to the folder associated with the given data type.
* @param dataType
* @return /absolute/path/to/folder/
*/
std::filesystem::path absolutePath(const std::string &dataType);

/**
* Returns a path to a resource called @resourceName of type @dataType with appropriate extension.
* @param type
* @param resourceName
* @return /path/to/folder/then/resource.type
*/
std::filesystem::path pathToResource(const std::string &type, const std::string &resourceName);

/**
* Ignores all lines starting with '#' in a given file.
* @param f
*/
void ignore_comments(std::ifstream &f);

} // STEngine::Filesystem

#endif //THE_STATION_FILESYSTEM_H
