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
* Throws an instance of std::logic_error if the file or value is not found.
* @param fileName
* @param key
* @return value at key
*/
std::string_view scanData(std::string_view fileName, std::string_view key);

/**
* Returns the default extension of the given data type.
* @return extension with a leading dot ('.')
*/
std::string_view getExtension(std::string_view dataType);

/**
* Returns the name of the folder associated with the given data type.
* @return folder name
*/
std::string_view getFolder(std::string_view dataType);

/**
* Returns the absolute path to the folder associated with the given data type.
* @param dataType
* @return /absolute/path/to/folder/
*/
std::filesystem::path absolutePath(std::string_view dataType);

/**
* Returns a path to a resource called @resourceName of type @dataType with appropriate extension.
* @param type
* @param resourceName
* @return /path/to/folder/then/resource.type
*/
std::filesystem::path pathToResource(std::string_view type, std::string_view resourceName);

/**
* Ignores all lines starting with '#' in a given file.
* @param f
*/
void ignore_comments(std::ifstream &f);

}  // namespace STEngine::Filesystem

#endif //THE_STATION_FILESYSTEM_H
